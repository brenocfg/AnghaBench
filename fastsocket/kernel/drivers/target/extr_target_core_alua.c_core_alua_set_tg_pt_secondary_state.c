#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct t10_alua_tg_pt_gp_member {int /*<<< orphan*/  tg_pt_gp_mem_lock; struct t10_alua_tg_pt_gp* tg_pt_gp; } ;
struct TYPE_2__ {int /*<<< orphan*/  cg_item; } ;
struct t10_alua_tg_pt_gp {int tg_pt_gp_trans_delay_msecs; int /*<<< orphan*/  tg_pt_gp_id; TYPE_1__ tg_pt_gp_group; int /*<<< orphan*/  tg_pt_gp_md_buf_len; } ;
struct se_port {int /*<<< orphan*/  sep_tg_pt_md_mutex; scalar_t__ sep_tg_pt_secondary_write_md; int /*<<< orphan*/  sep_tg_pt_secondary_stat; int /*<<< orphan*/  sep_tg_pt_secondary_offline; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALUA_STATUS_ALTERED_BY_EXPLICT_STPG ; 
 int /*<<< orphan*/  ALUA_STATUS_ALTERED_BY_IMPLICT_ALUA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  config_item_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  core_alua_update_tpg_secondary_metadata (struct t10_alua_tg_pt_gp_member*,struct se_port*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int core_alua_set_tg_pt_secondary_state(
	struct t10_alua_tg_pt_gp_member *tg_pt_gp_mem,
	struct se_port *port,
	int explict,
	int offline)
{
	struct t10_alua_tg_pt_gp *tg_pt_gp;
	unsigned char *md_buf;
	u32 md_buf_len;
	int trans_delay_msecs;

	spin_lock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
	tg_pt_gp = tg_pt_gp_mem->tg_pt_gp;
	if (!tg_pt_gp) {
		spin_unlock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
		pr_err("Unable to complete secondary state"
				" transition\n");
		return -EINVAL;
	}
	trans_delay_msecs = tg_pt_gp->tg_pt_gp_trans_delay_msecs;
	/*
	 * Set the secondary ALUA target port access state to OFFLINE
	 * or release the previously secondary state for struct se_port
	 */
	if (offline)
		atomic_set(&port->sep_tg_pt_secondary_offline, 1);
	else
		atomic_set(&port->sep_tg_pt_secondary_offline, 0);

	md_buf_len = tg_pt_gp->tg_pt_gp_md_buf_len;
	port->sep_tg_pt_secondary_stat = (explict) ?
			ALUA_STATUS_ALTERED_BY_EXPLICT_STPG :
			ALUA_STATUS_ALTERED_BY_IMPLICT_ALUA;

	pr_debug("Successful %s ALUA transition TG PT Group: %s ID: %hu"
		" to secondary access state: %s\n", (explict) ? "explict" :
		"implict", config_item_name(&tg_pt_gp->tg_pt_gp_group.cg_item),
		tg_pt_gp->tg_pt_gp_id, (offline) ? "OFFLINE" : "ONLINE");

	spin_unlock(&tg_pt_gp_mem->tg_pt_gp_mem_lock);
	/*
	 * Do the optional transition delay after we set the secondary
	 * ALUA access state.
	 */
	if (trans_delay_msecs != 0)
		msleep_interruptible(trans_delay_msecs);
	/*
	 * See if we need to update the ALUA fabric port metadata for
	 * secondary state and status
	 */
	if (port->sep_tg_pt_secondary_write_md) {
		md_buf = kzalloc(md_buf_len, GFP_KERNEL);
		if (!md_buf) {
			pr_err("Unable to allocate md_buf for"
				" secondary ALUA access metadata\n");
			return -ENOMEM;
		}
		mutex_lock(&port->sep_tg_pt_md_mutex);
		core_alua_update_tpg_secondary_metadata(tg_pt_gp_mem, port,
				md_buf, md_buf_len);
		mutex_unlock(&port->sep_tg_pt_md_mutex);

		kfree(md_buf);
	}

	return 0;
}