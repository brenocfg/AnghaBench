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
typedef  scalar_t__ s32 ;
struct TYPE_2__ {scalar_t__ seek_time; } ;

/* Variables and functions */
 TYPE_1__ private_ogg ; 

void SetTimeOgg(s32 time_pos)
{
  if (time_pos >= 0)
    private_ogg.seek_time = time_pos;
}