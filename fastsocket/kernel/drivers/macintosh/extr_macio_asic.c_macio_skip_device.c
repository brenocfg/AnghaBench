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
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int macio_skip_device(struct device_node *np)
{
	if (strncmp(np->name, "battery", 7) == 0)
		return 1;
	if (strncmp(np->name, "escc-legacy", 11) == 0)
		return 1;
	return 0;
}