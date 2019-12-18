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
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct fchs_s {int dummy; } ;
struct fc_els_cmd_s {int /*<<< orphan*/  els_code; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_ACC ; 
 int /*<<< orphan*/  fc_els_rsp_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_els_cmd_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_ls_acc_build(struct fchs_s *fchs, struct fc_els_cmd_s *els_cmd, u32 d_id,
		u32 s_id, __be16 ox_id)
{
	fc_els_rsp_build(fchs, d_id, s_id, ox_id);
	memset(els_cmd, 0, sizeof(struct fc_els_cmd_s));
	els_cmd->els_code = FC_ELS_ACC;

	return sizeof(struct fc_els_cmd_s);
}