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
struct TYPE_2__ {int cssid; int id; } ;
struct chp_link {int fla; TYPE_1__ chpid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_TRACE_EVENT (int,char*) ; 
 int /*<<< orphan*/  __s390_process_res_acc ; 
 int /*<<< orphan*/  css_wait_for_slow_path () ; 
 int /*<<< orphan*/  for_each_subchannel_staged (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct chp_link*) ; 
 int /*<<< orphan*/  s390_process_res_acc_new_sch ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 

__attribute__((used)) static void s390_process_res_acc(struct chp_link *link)
{
	char dbf_txt[15];

	sprintf(dbf_txt, "accpr%x.%02x", link->chpid.cssid,
		link->chpid.id);
	CIO_TRACE_EVENT( 2, dbf_txt);
	if (link->fla != 0) {
		sprintf(dbf_txt, "fla%x", link->fla);
		CIO_TRACE_EVENT( 2, dbf_txt);
	}
	/* Wait until previous actions have settled. */
	css_wait_for_slow_path();
	/*
	 * I/O resources may have become accessible.
	 * Scan through all subchannels that may be concerned and
	 * do a validation on those.
	 * The more information we have (info), the less scanning
	 * will we have to do.
	 */
	for_each_subchannel_staged(__s390_process_res_acc,
				   s390_process_res_acc_new_sch, link);
}