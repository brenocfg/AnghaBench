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
struct chsc_sei_area {int flags; int cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,...) ; 
 int /*<<< orphan*/  chsc_process_sei_chp_avail (struct chsc_sei_area*) ; 
 int /*<<< orphan*/  chsc_process_sei_chp_config (struct chsc_sei_area*) ; 
 int /*<<< orphan*/  chsc_process_sei_link_incident (struct chsc_sei_area*) ; 
 int /*<<< orphan*/  chsc_process_sei_res_acc (struct chsc_sei_area*) ; 
 int /*<<< orphan*/  chsc_process_sei_scm_avail (struct chsc_sei_area*) ; 
 int /*<<< orphan*/  chsc_process_sei_scm_change (struct chsc_sei_area*) ; 
 int /*<<< orphan*/  css_schedule_eval_all () ; 

__attribute__((used)) static void chsc_process_sei(struct chsc_sei_area *sei_area)
{
	/* Check if we might have lost some information. */
	if (sei_area->flags & 0x40) {
		CIO_CRW_EVENT(2, "chsc: event overflow\n");
		css_schedule_eval_all();
	}
	/* which kind of information was stored? */
	switch (sei_area->cc) {
	case 1: /* link incident*/
		chsc_process_sei_link_incident(sei_area);
		break;
	case 2: /* i/o resource accessibility */
		chsc_process_sei_res_acc(sei_area);
		break;
	case 7: /* channel-path-availability information */
		chsc_process_sei_chp_avail(sei_area);
		break;
	case 8: /* channel-path-configuration notification */
		chsc_process_sei_chp_config(sei_area);
		break;
	case 12: /* scm change notification */
		chsc_process_sei_scm_change(sei_area);
		break;
	case 14: /* scm available notification */
		chsc_process_sei_scm_avail(sei_area);
		break;
	default: /* other stuff */
		CIO_CRW_EVENT(4, "chsc: unhandled sei content code %d\n",
			      sei_area->cc);
		break;
	}
}