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
struct dirent {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int strcoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int alphasort(const struct dirent **a, const struct dirent **b)
{
	return strcoll((*a)->d_name, (*b)->d_name);
}