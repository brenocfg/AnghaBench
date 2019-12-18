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
struct mce {int cs; } ;

/* Variables and functions */
 int IN_KERNEL ; 
 int IN_USER ; 

__attribute__((used)) static int error_context(struct mce *m)
{
	return ((m->cs & 3) == 3) ? IN_USER : IN_KERNEL;
}