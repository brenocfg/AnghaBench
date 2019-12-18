#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {TYPE_1__* channel; } ;
struct TYPE_3__ {int duty; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SD_MUTEX_UNLOCK () ; 
 TYPE_2__ SIGMADELTA ; 

void sigmaDeltaWrite(uint8_t channel, uint8_t duty) //chan 0-7 duty 8 bit
{
    if(channel > 7) {
        return;
    }
    duty -= 128;
    SD_MUTEX_LOCK();
    SIGMADELTA.channel[channel].duty = duty;
    SD_MUTEX_UNLOCK();
}