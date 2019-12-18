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
struct link {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ WORKING_UNKNOWN ; 

__attribute__((used)) static int link_working_unknown(struct link *l_ptr)
{
	return (l_ptr->state == WORKING_UNKNOWN);
}