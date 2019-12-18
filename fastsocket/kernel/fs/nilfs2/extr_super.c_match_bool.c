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
struct TYPE_3__ {int to; int from; } ;
typedef  TYPE_1__ substring_t ;

/* Variables and functions */
 scalar_t__ strncmp (int,char*,int) ; 

__attribute__((used)) static int match_bool(substring_t *s, int *result)
{
	int len = s->to - s->from;

	if (strncmp(s->from, "on", len) == 0)
		*result = 1;
	else if (strncmp(s->from, "off", len) == 0)
		*result = 0;
	else
		return 1;
	return 0;
}