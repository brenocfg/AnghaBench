#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  na_atime; } ;
struct TYPE_5__ {scalar_t__ am_timeo; int /*<<< orphan*/  am_ttl; TYPE_1__ am_fattr; scalar_t__ am_timeo_w; } ;
typedef  TYPE_2__ am_node ;

/* Variables and functions */
 int /*<<< orphan*/  clocktime (int /*<<< orphan*/ *) ; 

void
new_ttl(am_node *mp)
{
  mp->am_timeo_w = 0;
  mp->am_ttl = clocktime(&mp->am_fattr.na_atime);
  mp->am_ttl += mp->am_timeo;	/* sun's -tl option */
}