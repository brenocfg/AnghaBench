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
 size_t AMU_TYPE_TCP ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 TYPE_1__ gopt ; 

__attribute__((used)) static int
gopt_nfs_retry_interval_tcp(const char *val)
{
  gopt.amfs_auto_timeo[AMU_TYPE_TCP] = atoi(val);
  return 0;
}