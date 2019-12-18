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
struct TYPE_2__ {scalar_t__ exec_map_timeout; } ;

/* Variables and functions */
 scalar_t__ AMFS_EXEC_MAP_TIMEOUT ; 
 scalar_t__ atoi (char const*) ; 
 TYPE_1__ gopt ; 

__attribute__((used)) static int
gopt_exec_map_timeout(const char *val)
{
  gopt.exec_map_timeout = atoi(val);
  if (gopt.exec_map_timeout <= 0)
    gopt.exec_map_timeout = AMFS_EXEC_MAP_TIMEOUT; /* default exec map timeout */
  return 0;
}