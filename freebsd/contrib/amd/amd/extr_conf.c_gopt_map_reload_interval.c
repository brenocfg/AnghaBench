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
struct TYPE_2__ {scalar_t__ map_reload_interval; } ;

/* Variables and functions */
 scalar_t__ ONE_HOUR ; 
 scalar_t__ atoi (char const*) ; 
 TYPE_1__ gopt ; 

__attribute__((used)) static int
gopt_map_reload_interval(const char *val)
{
  gopt.map_reload_interval = atoi(val);
  if (gopt.map_reload_interval <= 0)
    gopt.map_reload_interval = ONE_HOUR;
  return 0;
}