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
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int dummy; } ;
struct fc_tprlo_s {int page_len; int /*<<< orphan*/  payload_len; TYPE_1__* tprlo_params; int /*<<< orphan*/  command; } ;
typedef  enum fc_tprlo_type { ____Placeholder_fc_tprlo_type } fc_tprlo_type ;
struct TYPE_2__ {int global_process_logout; int tpo_nport_valid; int /*<<< orphan*/  tpo_nport_id; scalar_t__ resp_process_assc; scalar_t__ orig_process_assc; scalar_t__ rpa_valid; scalar_t__ opa_valid; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_ELS_TPRLO ; 
 int FC_GLOBAL_LOGO ; 
 int FC_TPR_LOGO ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  fc_els_req_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct fc_tprlo_s*,int /*<<< orphan*/ ,int) ; 

u16
fc_tprlo_build(struct fchs_s *fchs, u32 d_id, u32 s_id, u16 ox_id,
	       int num_pages, enum fc_tprlo_type tprlo_type, u32 tpr_id)
{
	struct fc_tprlo_s *tprlo = (struct fc_tprlo_s *) (fchs + 1);
	int             page;

	fc_els_req_build(fchs, d_id, s_id, ox_id);
	memset(tprlo, 0, (num_pages * 16) + 4);
	tprlo->command = FC_ELS_TPRLO;
	tprlo->page_len = 0x10;
	tprlo->payload_len = cpu_to_be16((num_pages * 16) + 4);

	for (page = 0; page < num_pages; page++) {
		tprlo->tprlo_params[page].type = FC_TYPE_FCP;
		tprlo->tprlo_params[page].opa_valid = 0;
		tprlo->tprlo_params[page].rpa_valid = 0;
		tprlo->tprlo_params[page].orig_process_assc = 0;
		tprlo->tprlo_params[page].resp_process_assc = 0;
		if (tprlo_type == FC_GLOBAL_LOGO) {
			tprlo->tprlo_params[page].global_process_logout = 1;
		} else if (tprlo_type == FC_TPR_LOGO) {
			tprlo->tprlo_params[page].tpo_nport_valid = 1;
			tprlo->tprlo_params[page].tpo_nport_id = (tpr_id);
		}
	}

	return be16_to_cpu(tprlo->payload_len);
}