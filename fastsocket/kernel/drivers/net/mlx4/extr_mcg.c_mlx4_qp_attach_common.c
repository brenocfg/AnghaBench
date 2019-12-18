#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct mlx4_qp {unsigned int qpn; } ;
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  bitmap; } ;
struct mlx4_priv {TYPE_2__ mcg_table; } ;
struct mlx4_mgm {void* next_gid_index; void* members_count; void** qp; int /*<<< orphan*/  gid; } ;
struct TYPE_3__ {int num_mgms; int num_qp_per_mgm; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {struct mlx4_mgm* buf; } ;
typedef  enum mlx4_steer_type { ____Placeholder_mlx4_steer_type } mlx4_steer_type ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 unsigned int MGM_BLCK_LB_BIT ; 
 unsigned int MGM_QPN_MASK ; 
 int MLX4_PROT_ETH ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 unsigned int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  existing_steering_entry (struct mlx4_dev*,int,int,int,unsigned int) ; 
 int find_entry (struct mlx4_dev*,int,int*,int,struct mlx4_cmd_mailbox*,int*,int*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memset (struct mlx4_mgm*,int /*<<< orphan*/ ,int) ; 
 int mlx4_READ_ENTRY (struct mlx4_dev*,int,struct mlx4_cmd_mailbox*) ; 
 int mlx4_WRITE_ENTRY (struct mlx4_dev*,int,struct mlx4_cmd_mailbox*) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_bitmap_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_bitmap_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx4_dbg (struct mlx4_dev*,char*,unsigned int) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,...) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_steering_entry (struct mlx4_dev*,int,int,int,unsigned int) ; 

int mlx4_qp_attach_common(struct mlx4_dev *dev, struct mlx4_qp *qp, u8 gid[16],
			  int block_mcast_loopback, enum mlx4_protocol prot,
			  enum mlx4_steer_type steer)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_mgm *mgm;
	u32 members_count;
	int index, prev;
	int link = 0;
	int i;
	int err;
	u8 port = gid[5];
	u8 new_entry = 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);
	mgm = mailbox->buf;

	mutex_lock(&priv->mcg_table.mutex);
	err = find_entry(dev, port, gid, prot,
			 mailbox, &prev, &index);
	if (err)
		goto out;

	if (index != -1) {
		if (!(be32_to_cpu(mgm->members_count) & 0xffffff)) {
			new_entry = 1;
			memcpy(mgm->gid, gid, 16);
		}
	} else {
		link = 1;

		index = mlx4_bitmap_alloc(&priv->mcg_table.bitmap);
		if (index == -1) {
			mlx4_err(dev, "No AMGM entries left\n");
			err = -ENOMEM;
			goto out;
		}
		index += dev->caps.num_mgms;

		new_entry = 1;
		memset(mgm, 0, sizeof *mgm);
		memcpy(mgm->gid, gid, 16);
	}

	members_count = be32_to_cpu(mgm->members_count) & 0xffffff;
	if (members_count == dev->caps.num_qp_per_mgm) {
		mlx4_err(dev, "MGM at index %x is full.\n", index);
		err = -ENOMEM;
		goto out;
	}

	for (i = 0; i < members_count; ++i)
		if ((be32_to_cpu(mgm->qp[i]) & MGM_QPN_MASK) == qp->qpn) {
			mlx4_dbg(dev, "QP %06x already a member of MGM\n", qp->qpn);
			err = 0;
			goto out;
		}

	if (block_mcast_loopback)
		mgm->qp[members_count++] = cpu_to_be32((qp->qpn & MGM_QPN_MASK) |
						       (1U << MGM_BLCK_LB_BIT));
	else
		mgm->qp[members_count++] = cpu_to_be32(qp->qpn & MGM_QPN_MASK);

	mgm->members_count = cpu_to_be32(members_count | (u32) prot << 30);

	err = mlx4_WRITE_ENTRY(dev, index, mailbox);
	if (err)
		goto out;

	if (!link)
		goto out;

	err = mlx4_READ_ENTRY(dev, prev, mailbox);
	if (err)
		goto out;

	mgm->next_gid_index = cpu_to_be32(index << 6);

	err = mlx4_WRITE_ENTRY(dev, prev, mailbox);
	if (err)
		goto out;

out:
	if (prot == MLX4_PROT_ETH) {
		/* manage the steering entry for promisc mode */
		if (new_entry)
			new_steering_entry(dev, port, steer, index, qp->qpn);
		else
			existing_steering_entry(dev, port, steer,
						index, qp->qpn);
	}
	if (err && link && index != -1) {
		if (index < dev->caps.num_mgms)
			mlx4_warn(dev, "Got AMGM index %d < %d",
				  index, dev->caps.num_mgms);
		else
			mlx4_bitmap_free(&priv->mcg_table.bitmap,
					 index - dev->caps.num_mgms);
	}
	mutex_unlock(&priv->mcg_table.mutex);

	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}