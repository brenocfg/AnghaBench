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
typedef  int u_int32_t ;
struct sastat {int /*<<< orphan*/  spi; } ;

/* Variables and functions */
 scalar_t__ key_getsastatbyspi_one (int /*<<< orphan*/ ,struct sastat*) ; 

__attribute__((used)) static int
key_getsastatbyspi (struct sastat *stat_arg,
					u_int32_t      max_stat_arg,
					struct sastat *stat_res,
					u_int32_t     *max_stat_res)
{
	int cur, found = 0;
	
	if (stat_arg == NULL ||
	    stat_res == NULL ||
	    max_stat_res == NULL) {
		return -1;
	}
	
	for (cur = 0; cur < max_stat_arg; cur++) {
		if (key_getsastatbyspi_one(stat_arg[cur].spi,
								   &stat_res[found]) == 0) {
			found++;
		}
	}
	*max_stat_res = found;
	
	if (found) {
		return 0;
	}
	return -1;
}