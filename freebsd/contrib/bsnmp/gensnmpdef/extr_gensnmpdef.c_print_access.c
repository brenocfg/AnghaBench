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
typedef  scalar_t__ SmiAccess ;

/* Variables and functions */
 scalar_t__ SMI_ACCESS_READ_ONLY ; 
 scalar_t__ SMI_ACCESS_READ_WRITE ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
print_access(SmiAccess a)
{
	if (a == SMI_ACCESS_READ_ONLY)
		printf(" GET");
	else if (a == SMI_ACCESS_READ_WRITE)
		printf(" GET SET");
}