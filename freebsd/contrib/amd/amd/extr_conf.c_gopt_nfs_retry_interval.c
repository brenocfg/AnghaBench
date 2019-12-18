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
struct TYPE_2__ {int /*<<< orphan*/ * amfs_auto_timeo; } ;

/* Variables and functions */
 int AMU_TYPE_MAX ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 TYPE_1__ gopt ; 

__attribute__((used)) static int
gopt_nfs_retry_interval(const char *val)
{
  int i;

  for (i=0; i<AMU_TYPE_MAX; ++i)
    gopt.amfs_auto_timeo[i] = atoi(val);
  return 0;
}