#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct iwl_trans {int dummy; } ;
struct iwl_test {struct iwl_trans* trans; } ;

/* Variables and functions */
 int EINVAL ; 
 int EMSGSIZE ; 
 int ENOMEM ; 
 int ENOMSG ; 
 scalar_t__ FH_MEM_UPPER_BOUND ; 
 int /*<<< orphan*/  IWL_DEBUG_INFO (struct iwl_trans*,char*,scalar_t__) ; 
 int /*<<< orphan*/  IWL_ERR (struct iwl_trans*,char*,...) ; 
 size_t IWL_TM_ATTR_COMMAND ; 
 size_t IWL_TM_ATTR_REG_OFFSET ; 
 size_t IWL_TM_ATTR_REG_VALUE32 ; 
 size_t IWL_TM_ATTR_REG_VALUE8 ; 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_READ32 130 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE32 129 
#define  IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE8 128 
 scalar_t__ iwl_read_direct32 (struct iwl_trans*,scalar_t__) ; 
 struct sk_buff* iwl_test_alloc_reply (struct iwl_test*,int) ; 
 int iwl_test_reply (struct iwl_test*,struct sk_buff*) ; 
 int /*<<< orphan*/  iwl_write8 (struct iwl_trans*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  iwl_write_direct32 (struct iwl_trans*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 scalar_t__ nla_get_u32 (struct nlattr*) ; 
 scalar_t__ nla_get_u8 (struct nlattr*) ; 
 int /*<<< orphan*/  nla_put_u32 (struct sk_buff*,size_t,scalar_t__) ; 

__attribute__((used)) static int iwl_test_reg(struct iwl_test *tst, struct nlattr **tb)
{
	u32 ofs, val32, cmd;
	u8 val8;
	struct sk_buff *skb;
	int status = 0;
	struct iwl_trans *trans = tst->trans;

	if (!tb[IWL_TM_ATTR_REG_OFFSET]) {
		IWL_ERR(trans, "Missing reg offset\n");
		return -ENOMSG;
	}

	ofs = nla_get_u32(tb[IWL_TM_ATTR_REG_OFFSET]);
	IWL_DEBUG_INFO(trans, "test reg access cmd offset=0x%x\n", ofs);

	cmd = nla_get_u32(tb[IWL_TM_ATTR_COMMAND]);

	/*
	 * Allow access only to FH/CSR/HBUS in direct mode.
	 * Since we don't have the upper bounds for the CSR and HBUS segments,
	 * we will use only the upper bound of FH for sanity check.
	 */
	if (ofs >= FH_MEM_UPPER_BOUND) {
		IWL_ERR(trans, "offset out of segment (0x0 - 0x%x)\n",
			FH_MEM_UPPER_BOUND);
		return -EINVAL;
	}

	switch (cmd) {
	case IWL_TM_CMD_APP2DEV_DIRECT_REG_READ32:
		val32 = iwl_read_direct32(tst->trans, ofs);
		IWL_DEBUG_INFO(trans, "32 value to read 0x%x\n", val32);

		skb = iwl_test_alloc_reply(tst, 20);
		if (!skb) {
			IWL_ERR(trans, "Memory allocation fail\n");
			return -ENOMEM;
		}
		if (nla_put_u32(skb, IWL_TM_ATTR_REG_VALUE32, val32))
			goto nla_put_failure;
		status = iwl_test_reply(tst, skb);
		if (status < 0)
			IWL_ERR(trans, "Error sending msg : %d\n", status);
		break;

	case IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE32:
		if (!tb[IWL_TM_ATTR_REG_VALUE32]) {
			IWL_ERR(trans, "Missing value to write\n");
			return -ENOMSG;
		} else {
			val32 = nla_get_u32(tb[IWL_TM_ATTR_REG_VALUE32]);
			IWL_DEBUG_INFO(trans, "32b write val=0x%x\n", val32);
			iwl_write_direct32(tst->trans, ofs, val32);
		}
		break;

	case IWL_TM_CMD_APP2DEV_DIRECT_REG_WRITE8:
		if (!tb[IWL_TM_ATTR_REG_VALUE8]) {
			IWL_ERR(trans, "Missing value to write\n");
			return -ENOMSG;
		} else {
			val8 = nla_get_u8(tb[IWL_TM_ATTR_REG_VALUE8]);
			IWL_DEBUG_INFO(trans, "8b write val=0x%x\n", val8);
			iwl_write8(tst->trans, ofs, val8);
		}
		break;

	default:
		IWL_ERR(trans, "Unknown test register cmd ID\n");
		return -ENOMSG;
	}

	return status;

nla_put_failure:
	kfree_skb(skb);
	return -EMSGSIZE;
}