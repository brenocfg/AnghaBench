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
 int /*<<< orphan*/ * action_name ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void action_result(unsigned long pfn, char *msg, int result)
{
	pr_err("MCE %#lx: %s page recovery: %s\n",
		pfn, msg, action_name[result]);
}