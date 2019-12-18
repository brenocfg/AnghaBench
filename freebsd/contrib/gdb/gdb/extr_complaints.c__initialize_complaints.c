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

/* Variables and functions */
 int /*<<< orphan*/  add_setshow_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  stop_whining ; 
 int /*<<< orphan*/  var_zinteger ; 

void
_initialize_complaints (void)
{
  add_setshow_cmd ("complaints", class_support, var_zinteger,
		   &stop_whining,
		   "Set max number of complaints about incorrect symbols.",
		   "Show max number of complaints about incorrect symbols.",
		   NULL, NULL,
		   &setlist, &showlist);

}