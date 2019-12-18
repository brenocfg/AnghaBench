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
struct target_address {int dummy; } ;

/* Variables and functions */
 struct target_address* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_addresslist ; 

struct target_address *
target_first_address(void)
{
	return (SLIST_FIRST(&target_addresslist));
}