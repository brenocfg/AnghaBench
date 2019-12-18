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
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ,char,char*) ; 
 int /*<<< orphan*/  demand_empty_rest_of_line () ; 

__attribute__((used)) static void
s_bad_end (int endr)
{
  as_warn (_(".end%c encountered without preceeding %s"),
	   endr ? 'r' : 'm',
	   endr ? ".rept, .irp, or .irpc" : ".macro");
  demand_empty_rest_of_line ();
}