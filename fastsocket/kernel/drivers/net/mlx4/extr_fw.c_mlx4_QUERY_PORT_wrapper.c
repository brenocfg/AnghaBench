#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct mlx4_vhcr {size_t in_modifier; } ;
struct TYPE_14__ {TYPE_5__* vf_admin; TYPE_3__* vf_oper; } ;
struct TYPE_15__ {TYPE_6__ master; } ;
struct mlx4_priv {TYPE_7__ mfunc; } ;
struct TYPE_16__ {int function; int* port_type; int* pkey_table_len; } ;
struct mlx4_dev {TYPE_8__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct mlx4_cmd_info {int dummy; } ;
struct TYPE_13__ {TYPE_4__* vport; } ;
struct TYPE_12__ {int mac; } ;
struct TYPE_11__ {TYPE_2__* vport; } ;
struct TYPE_9__ {int mac; } ;
struct TYPE_10__ {TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_PORT ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  MLX4_GET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX4_PUT (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int MLX4_VF_PORT_NO_LINK_SENSE_MASK ; 
 int /*<<< orphan*/  QUERY_PORT_CUR_MAX_GID_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_CUR_MAX_PKEY_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_MAC_OFFSET ; 
 int /*<<< orphan*/  QUERY_PORT_SUPPORTED_TYPE_OFFSET ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_priv* mlx4_priv (struct mlx4_dev*) ; 

int mlx4_QUERY_PORT_wrapper(struct mlx4_dev *dev, int slave,
			    struct mlx4_vhcr *vhcr,
			    struct mlx4_cmd_mailbox *inbox,
			    struct mlx4_cmd_mailbox *outbox,
			    struct mlx4_cmd_info *cmd)
{
	struct mlx4_priv *priv = mlx4_priv(dev);
	u64 def_mac;
	u8 port_type;
	u16 short_field;
	int err;

#define MLX4_VF_PORT_NO_LINK_SENSE_MASK	0xE0
#define QUERY_PORT_CUR_MAX_PKEY_OFFSET	0x0c
#define QUERY_PORT_CUR_MAX_GID_OFFSET	0x0e

	err = mlx4_cmd_box(dev, 0, outbox->dma, vhcr->in_modifier, 0,
			   MLX4_CMD_QUERY_PORT, MLX4_CMD_TIME_CLASS_B,
			   MLX4_CMD_NATIVE);

	if (!err && dev->caps.function != slave) {
		/* if config MAC in DB use it */
		if (priv->mfunc.master.vf_oper[slave].vport[vhcr->in_modifier].state.mac)
			def_mac = priv->mfunc.master.vf_oper[slave].vport[vhcr->in_modifier].state.mac;
		else {
			/* set slave default_mac address */
			MLX4_GET(def_mac, outbox->buf, QUERY_PORT_MAC_OFFSET);
			def_mac += slave << 8;
			priv->mfunc.master.vf_admin[slave].vport[vhcr->in_modifier].mac = def_mac;
		}

		MLX4_PUT(outbox->buf, def_mac, QUERY_PORT_MAC_OFFSET);

		/* get port type - currently only eth is enabled */
		MLX4_GET(port_type, outbox->buf,
			 QUERY_PORT_SUPPORTED_TYPE_OFFSET);

		/* No link sensing allowed */
		port_type &= MLX4_VF_PORT_NO_LINK_SENSE_MASK;
		/* set port type to currently operating port type */
		port_type |= (dev->caps.port_type[vhcr->in_modifier] & 0x3);

		MLX4_PUT(outbox->buf, port_type,
			 QUERY_PORT_SUPPORTED_TYPE_OFFSET);

		short_field = 1; /* slave max gids */
		MLX4_PUT(outbox->buf, short_field,
			 QUERY_PORT_CUR_MAX_GID_OFFSET);

		short_field = dev->caps.pkey_table_len[vhcr->in_modifier];
		MLX4_PUT(outbox->buf, short_field,
			 QUERY_PORT_CUR_MAX_PKEY_OFFSET);
	}

	return err;
}