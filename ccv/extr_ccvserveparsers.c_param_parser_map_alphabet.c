#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  property; } ;
typedef  TYPE_1__ param_dispatch_t ;

/* Variables and functions */
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int param_parser_map_alphabet(const param_dispatch_t* param_map, size_t len)
{
	int i;
	for (i = 1; i < len; i++)
		if (strcmp(param_map[i - 1].property, param_map[i].property) >= 0)
			return -1;
	return 0;
}