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
struct fchs_s {int dummy; } ;
struct fc_ls_rjt_s {int /*<<< orphan*/  reason_code; } ;
struct fc_els_cmd_s {int els_code; } ;
typedef  enum fc_parse_status { ____Placeholder_fc_parse_status } fc_parse_status ;

/* Variables and functions */
#define  FC_ELS_ACC 129 
#define  FC_ELS_LS_RJT 128 
 int /*<<< orphan*/  FC_LS_RJT_RSN_LOGICAL_BUSY ; 
 int FC_PARSE_BUSY ; 
 int FC_PARSE_FAILURE ; 
 int FC_PARSE_OK ; 

enum fc_parse_status
fc_els_rsp_parse(struct fchs_s *fchs, int len)
{
	struct fc_els_cmd_s *els_cmd = (struct fc_els_cmd_s *) (fchs + 1);
	struct fc_ls_rjt_s *ls_rjt = (struct fc_ls_rjt_s *) els_cmd;

	len = len;

	switch (els_cmd->els_code) {
	case FC_ELS_LS_RJT:
		if (ls_rjt->reason_code == FC_LS_RJT_RSN_LOGICAL_BUSY)
			return FC_PARSE_BUSY;
		else
			return FC_PARSE_FAILURE;

	case FC_ELS_ACC:
		return FC_PARSE_OK;
	}
	return FC_PARSE_OK;
}