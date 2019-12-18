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
typedef  int s32 ;
struct TYPE_2__ {scalar_t__ fd; int /*<<< orphan*/  vf; } ;

/* Variables and functions */
 scalar_t__ ogg_thread_running ; 
 scalar_t__ ov_time_tell (int /*<<< orphan*/ *) ; 
 TYPE_1__ private_ogg ; 

s32 GetTimeOgg()
{
  int ret;
  if (ogg_thread_running == 0 || private_ogg.fd < 0)
    return 0;
  ret = ((s32) ov_time_tell(&private_ogg.vf));
  if (ret < 0)
    ret = 0;

  return ret;
}