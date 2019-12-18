#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int id; scalar_t__* sid; scalar_t__ name; } ;

/* Variables and functions */
 TYPE_1__* curves ; 
 scalar_t__ eqstr (scalar_t__,char const*) ; 

int
get_curve_by_name(const char *str)
{
	size_t u, v;

	for (u = 0; curves[u].name; u ++) {
		for (v = 0; curves[u].sid[v]; v ++) {
			if (eqstr(curves[u].sid[v], str)) {
				return curves[u].id;
			}
		}
	}
	return -1;
}