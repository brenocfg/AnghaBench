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
struct chsc_sei_area {int rs; int vf; int /*<<< orphan*/  fla; int /*<<< orphan*/  rsid; } ;
struct chp_id {int /*<<< orphan*/  id; } ;
struct chp_link {int fla_mask; int /*<<< orphan*/  fla; struct chp_id chpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,int,int /*<<< orphan*/ ) ; 
 int chp_get_status (struct chp_id) ; 
 int /*<<< orphan*/  chp_id_init (struct chp_id*) ; 
 int /*<<< orphan*/  chp_new (struct chp_id) ; 
 int /*<<< orphan*/  memset (struct chp_link*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s390_process_res_acc (struct chp_link*) ; 

__attribute__((used)) static void chsc_process_sei_res_acc(struct chsc_sei_area *sei_area)
{
	struct chp_link link;
	struct chp_id chpid;
	int status;

	CIO_CRW_EVENT(4, "chsc: resource accessibility event (rs=%02x, "
		      "rs_id=%04x)\n", sei_area->rs, sei_area->rsid);
	if (sei_area->rs != 4)
		return;
	chp_id_init(&chpid);
	chpid.id = sei_area->rsid;
	/* allocate a new channel path structure, if needed */
	status = chp_get_status(chpid);
	if (status < 0)
		chp_new(chpid);
	else if (!status)
		return;
	memset(&link, 0, sizeof(struct chp_link));
	link.chpid = chpid;
	if ((sei_area->vf & 0xc0) != 0) {
		link.fla = sei_area->fla;
		if ((sei_area->vf & 0xc0) == 0xc0)
			/* full link address */
			link.fla_mask = 0xffff;
		else
			/* link address */
			link.fla_mask = 0xff00;
	}
	s390_process_res_acc(&link);
}