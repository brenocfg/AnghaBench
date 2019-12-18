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
struct error_sparse_map {int start; int end; } ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int INT_MAX ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static int
err_sparse_mapit(int old, const struct error_sparse_map *map_table, int mapcnt)
{
	boolean_t found = FALSE;
	int ret = 0, i;

	for (i = 0; i < mapcnt; i++) {
		struct error_sparse_map entry = map_table[i];

		if (entry.start <= old && old <= entry.end) {
			ret += old - entry.start;
			found = TRUE;
			break;
		}
		ret += entry.end - entry.start + 1;
	}

	return (found)? ret : INT_MAX;
}