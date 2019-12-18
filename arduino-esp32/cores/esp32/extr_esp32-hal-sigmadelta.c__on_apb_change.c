#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ apb_change_ev_t ;
struct TYPE_5__ {int clk_en; } ;
struct TYPE_6__ {TYPE_2__ cg; TYPE_1__* channel; } ;
struct TYPE_4__ {int prescale; } ;

/* Variables and functions */
 scalar_t__ APB_BEFORE_CHANGE ; 
 int /*<<< orphan*/  SD_MUTEX_LOCK () ; 
 int /*<<< orphan*/  SD_MUTEX_UNLOCK () ; 
 TYPE_3__ SIGMADELTA ; 

__attribute__((used)) static void _on_apb_change(void * arg, apb_change_ev_t ev_type, uint32_t old_apb, uint32_t new_apb){
    if(old_apb == new_apb){
        return;
    }
    uint32_t iarg = (uint32_t)arg;
    uint8_t channel = iarg;
    if(ev_type == APB_BEFORE_CHANGE){
        SIGMADELTA.cg.clk_en = 0;
    } else {
        old_apb /= 1000000;
        new_apb /= 1000000;
        SD_MUTEX_LOCK();
        uint32_t old_prescale = SIGMADELTA.channel[channel].prescale + 1;
        SIGMADELTA.channel[channel].prescale = ((new_apb * old_prescale) / old_apb) - 1;
        SIGMADELTA.cg.clk_en = 0;
        SIGMADELTA.cg.clk_en = 1;
        SD_MUTEX_UNLOCK();
    }
}