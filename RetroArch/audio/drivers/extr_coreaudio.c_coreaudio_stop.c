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
struct TYPE_2__ {int is_paused; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ coreaudio_t ;

/* Variables and functions */
 scalar_t__ AudioOutputUnitStop (int /*<<< orphan*/ ) ; 
 scalar_t__ noErr ; 

__attribute__((used)) static bool coreaudio_stop(void *data)
{
   coreaudio_t *dev = (coreaudio_t*)data;
   if (!dev)
      return false;
   dev->is_paused = (AudioOutputUnitStop(dev->dev) == noErr) ? true : false;
   return dev->is_paused ? true : false;
}