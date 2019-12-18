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
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  mnt_map ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_USER ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int
error_init(mnt_map *m, char *map, time_t *tp)
{
  plog(XLOG_USER, "No source data for map %s", map);
  *tp = 0;

  return 0;
}