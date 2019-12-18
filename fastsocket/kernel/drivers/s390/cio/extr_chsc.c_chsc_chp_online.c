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
struct chp_id {int cssid; int id; } ;
struct chp_link {struct chp_id chpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  __s390_process_res_acc ; 
 scalar_t__ chp_get_status (struct chp_id) ; 
 int /*<<< orphan*/  css_wait_for_slow_path () ; 
 int /*<<< orphan*/  for_each_subchannel_staged (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct chp_link*) ; 
 int /*<<< orphan*/  memset (struct chp_link*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int) ; 

void chsc_chp_online(struct chp_id chpid)
{
	char dbf_txt[15];
	struct chp_link link;

	sprintf(dbf_txt, "cadd%x.%02x", chpid.cssid, chpid.id);
	CIO_TRACE_EVENT(2, dbf_txt);

	if (chp_get_status(chpid) != 0) {
		memset(&link, 0, sizeof(struct chp_link));
		link.chpid = chpid;
		/* Wait until previous actions have settled. */
		css_wait_for_slow_path();
		for_each_subchannel_staged(__s390_process_res_acc, NULL,
					   &link);
	}
}