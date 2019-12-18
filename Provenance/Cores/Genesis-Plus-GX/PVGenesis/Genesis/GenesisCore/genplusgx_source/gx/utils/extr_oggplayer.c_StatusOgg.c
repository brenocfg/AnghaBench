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
struct TYPE_2__ {int flag; scalar_t__ eof; } ;

/* Variables and functions */
 scalar_t__ ogg_thread_running ; 
 TYPE_1__ private_ogg ; 

int StatusOgg()
{
  if (ogg_thread_running == 0)
    return -1; /* Error */
  else if (private_ogg.eof)
    return 255; /* EOF */
  else if (private_ogg.flag & 128)
    return 2; /* paused */
  else
    return 1; /* running */
}