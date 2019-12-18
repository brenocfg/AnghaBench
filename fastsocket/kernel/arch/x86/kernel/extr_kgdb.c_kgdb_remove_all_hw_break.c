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
struct hw_breakpoint {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * breakinfo ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void kgdb_remove_all_hw_break(void)
{
	int i;

	for (i = 0; i < 4; i++)
		memset(&breakinfo[i], 0, sizeof(struct hw_breakpoint));
}