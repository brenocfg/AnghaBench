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
struct c67x00_hcd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c67x00_do_work (struct c67x00_hcd*) ; 

__attribute__((used)) static void c67x00_sched_tasklet(unsigned long __c67x00)
{
	struct c67x00_hcd *c67x00 = (struct c67x00_hcd *)__c67x00;
	c67x00_do_work(c67x00);
}