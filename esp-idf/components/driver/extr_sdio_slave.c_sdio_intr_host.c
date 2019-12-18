#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ portBASE_TYPE ;
struct TYPE_7__ {int val; } ;
struct TYPE_6__ {int val; } ;
struct TYPE_10__ {TYPE_2__ slc0_int_clr; TYPE_1__ slc0_int_st; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* event_cb ) (int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/ * events; TYPE_3__ config; } ;

/* Variables and functions */
 int BIT (int) ; 
 TYPE_5__ SLC ; 
 TYPE_4__ context ; 
 scalar_t__ pdFALSE ; 
 int /*<<< orphan*/  portYIELD_FROM_ISR () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  xSemaphoreGiveFromISR (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void sdio_intr_host(void* arg)
{
    uint8_t int_val = SLC.slc0_int_st.val & 0xff;

    portBASE_TYPE yield = pdFALSE;
    SLC.slc0_int_clr.val = int_val;
    for(int i = 0; i < 8; i++) {
        if (BIT(i) & int_val) {
            if (context.config.event_cb != NULL) (*context.config.event_cb)(i);
            xSemaphoreGiveFromISR(context.events[i], &yield);
        }
    }
    if (yield) portYIELD_FROM_ISR();
}