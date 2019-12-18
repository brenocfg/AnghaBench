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
struct TYPE_4__ {int /*<<< orphan*/  pin; TYPE_1__* GPIOx; } ;
struct TYPE_3__ {int /*<<< orphan*/  BRR; int /*<<< orphan*/  BSRR; } ;

/* Variables and functions */
 size_t TLC59401_PIN_BLANK0 ; 
 size_t TLC59401_PIN_BLANK1 ; 
 size_t TLC59401_PIN_XLAT0 ; 
 size_t TLC59401_PIN_XLAT1 ; 
 scalar_t__ enableBlank ; 
 scalar_t__ isIdle () ; 
 int needLatch0 ; 
 int needLatch1 ; 
 TYPE_2__* pins_tlc59401 ; 

void TLC59401_Update(void) {
    bool doLatch0 = false;
    bool doLatch1 = false;
    static int callCount = 0;

    if( isIdle() ) {
        doLatch0 = needLatch0;
        doLatch1 = needLatch1;
    }

    if((callCount++ & 1) == 0) {
        if(enableBlank) {
            pins_tlc59401[TLC59401_PIN_BLANK0].GPIOx->BSRR = pins_tlc59401[TLC59401_PIN_BLANK0].pin;
        }
        //GPIO_WriteBit(pins_tlc59401[TLC59401_PIN_BLANK].GPIOx, pins_tlc59401[TLC59401_PIN_BLANK].pin, 1);
        if(doLatch0) {
            pins_tlc59401[TLC59401_PIN_XLAT0].GPIOx->BSRR = pins_tlc59401[TLC59401_PIN_XLAT0].pin;
            //GPIO_WriteBit(pins_tlc59401[TLC59401_PIN_XLAT].GPIOx, pins_tlc59401[TLC59401_PIN_XLAT].pin, 1);
        }
        // FIXME may need a short delay in here for high speed processors to meet 20ns minimum pulse duration
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        if(doLatch0) {
            pins_tlc59401[TLC59401_PIN_XLAT0].GPIOx->BRR = pins_tlc59401[TLC59401_PIN_XLAT0].pin;
            //GPIO_WriteBit(pins_tlc59401[TLC59401_PIN_XLAT].GPIOx, pins_tlc59401[TLC59401_PIN_XLAT].pin, 0);
            needLatch0 = false;
        }
        if(enableBlank) {
            pins_tlc59401[TLC59401_PIN_BLANK0].GPIOx->BRR = pins_tlc59401[TLC59401_PIN_BLANK0].pin;
        }
        //GPIO_WriteBit(pins_tlc59401[TLC59401_PIN_BLANK].GPIOx, pins_tlc59401[TLC59401_PIN_BLANK].pin, 0);
    } else {
        if(enableBlank) {
            pins_tlc59401[TLC59401_PIN_BLANK1].GPIOx->BSRR = pins_tlc59401[TLC59401_PIN_BLANK1].pin;
        }
        if(doLatch1) {
            pins_tlc59401[TLC59401_PIN_XLAT1].GPIOx->BSRR = pins_tlc59401[TLC59401_PIN_XLAT1].pin;
        }
        // FIXME may need a short delay in here for high speed processors to meet 20ns minimum pulse duration
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        if(doLatch1) {
            pins_tlc59401[TLC59401_PIN_XLAT1].GPIOx->BRR = pins_tlc59401[TLC59401_PIN_XLAT1].pin;
            needLatch1 = false;
        }
        if(enableBlank) {
            pins_tlc59401[TLC59401_PIN_BLANK1].GPIOx->BRR = pins_tlc59401[TLC59401_PIN_BLANK1].pin;
        }
    }

}