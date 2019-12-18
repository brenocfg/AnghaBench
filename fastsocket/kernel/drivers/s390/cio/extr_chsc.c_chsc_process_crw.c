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
struct crw {int /*<<< orphan*/  rsid; int /*<<< orphan*/  erc; int /*<<< orphan*/  anc; int /*<<< orphan*/  rsc; int /*<<< orphan*/  chn; int /*<<< orphan*/  oflw; int /*<<< orphan*/  slct; } ;
struct TYPE_4__ {int code; } ;
struct TYPE_3__ {int length; int code; } ;
struct chsc_sei_area {int flags; TYPE_2__ response; TYPE_1__ request; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,...) ; 
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 scalar_t__ chsc (struct chsc_sei_area*) ; 
 int /*<<< orphan*/  chsc_process_sei (struct chsc_sei_area*) ; 
 int /*<<< orphan*/  css_schedule_eval_all () ; 
 int /*<<< orphan*/  memset (struct chsc_sei_area*,int /*<<< orphan*/ ,int) ; 
 struct chsc_sei_area* sei_page ; 

__attribute__((used)) static void chsc_process_crw(struct crw *crw0, struct crw *crw1, int overflow)
{
	struct chsc_sei_area *sei_area;

	if (overflow) {
		css_schedule_eval_all();
		return;
	}
	CIO_CRW_EVENT(2, "CRW reports slct=%d, oflw=%d, "
		      "chn=%d, rsc=%X, anc=%d, erc=%X, rsid=%X\n",
		      crw0->slct, crw0->oflw, crw0->chn, crw0->rsc, crw0->anc,
		      crw0->erc, crw0->rsid);
	if (!sei_page)
		return;
	/* Access to sei_page is serialized through machine check handler
	 * thread, so no need for locking. */
	sei_area = sei_page;

	CIO_TRACE_EVENT(2, "prcss");
	do {
		memset(sei_area, 0, sizeof(*sei_area));
		sei_area->request.length = 0x0010;
		sei_area->request.code = 0x000e;
		if (chsc(sei_area))
			break;

		if (sei_area->response.code == 0x0001) {
			CIO_CRW_EVENT(4, "chsc: sei successful\n");
			chsc_process_sei(sei_area);
		} else {
			CIO_CRW_EVENT(2, "chsc: sei failed (rc=%04x)\n",
				      sei_area->response.code);
			break;
		}
	} while (sei_area->flags & 0x80);
}