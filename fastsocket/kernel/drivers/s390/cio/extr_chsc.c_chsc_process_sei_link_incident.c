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
struct chsc_sei_area {int rs; int /*<<< orphan*/  ccdf; int /*<<< orphan*/  rsid; } ;
struct chp_id {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,...) ; 
 int __get_chpid_from_lir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chp_id_init (struct chp_id*) ; 
 int /*<<< orphan*/  chsc_chp_offline (struct chp_id) ; 

__attribute__((used)) static void chsc_process_sei_link_incident(struct chsc_sei_area *sei_area)
{
	struct chp_id chpid;
	int id;

	CIO_CRW_EVENT(4, "chsc: link incident (rs=%02x, rs_id=%04x)\n",
		      sei_area->rs, sei_area->rsid);
	if (sei_area->rs != 4)
		return;
	id = __get_chpid_from_lir(sei_area->ccdf);
	if (id < 0)
		CIO_CRW_EVENT(4, "chsc: link incident - invalid LIR\n");
	else {
		chp_id_init(&chpid);
		chpid.id = id;
		chsc_chp_offline(chpid);
	}
}