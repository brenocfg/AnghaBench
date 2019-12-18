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
struct chsc_sei_area {int rs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO_CRW_EVENT (int,char*,...) ; 
 int scm_update_information () ; 

__attribute__((used)) static void chsc_process_sei_scm_change(struct chsc_sei_area *sei_area)
{
	int ret;

	CIO_CRW_EVENT(4, "chsc: scm change notification\n");
	if (sei_area->rs != 7)
		return;

	ret = scm_update_information();
	if (ret)
		CIO_CRW_EVENT(0, "chsc: updating change notification"
			      " failed (rc=%d).\n", ret);
}