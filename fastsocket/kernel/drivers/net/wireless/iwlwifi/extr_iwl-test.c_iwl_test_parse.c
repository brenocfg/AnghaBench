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
struct nlattr {int dummy; } ;
struct iwl_test {int /*<<< orphan*/  trans; } ;

/* Variables and functions */
 int ENOMSG ; 
 int /*<<< orphan*/  IWL_ERR (int /*<<< orphan*/ ,char*,...) ; 
 size_t IWL_TM_ATTR_COMMAND ; 
 scalar_t__ IWL_TM_ATTR_MAX ; 
 int /*<<< orphan*/  iwl_testmode_gnl_msg_policy ; 
 int nla_parse (struct nlattr**,scalar_t__,void*,int,int /*<<< orphan*/ ) ; 

int iwl_test_parse(struct iwl_test *tst, struct nlattr **tb,
		   void *data, int len)
{
	int result;

	result = nla_parse(tb, IWL_TM_ATTR_MAX - 1, data, len,
			iwl_testmode_gnl_msg_policy);
	if (result) {
		IWL_ERR(tst->trans, "Fail parse gnl msg: %d\n", result);
		return result;
	}

	/* IWL_TM_ATTR_COMMAND is absolutely mandatory */
	if (!tb[IWL_TM_ATTR_COMMAND]) {
		IWL_ERR(tst->trans, "Missing testmode command type\n");
		return -ENOMSG;
	}
	return 0;
}