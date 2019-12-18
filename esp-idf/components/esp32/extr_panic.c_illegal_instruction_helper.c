#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int pc; } ;
typedef  TYPE_1__ XtExcFrame ;

/* Variables and functions */
 int SOC_IROM_HIGH ; 
 int SOC_IROM_MASK_LOW ; 
 int /*<<< orphan*/  panicPutHex (int volatile) ; 
 int /*<<< orphan*/  panicPutStr (char*) ; 

__attribute__((used)) static void illegal_instruction_helper(XtExcFrame *frame)
{
    /* Print out memory around the instruction word */
    uint32_t epc = frame->pc;
    epc = (epc & ~0x3) - 4;

    /* check that the address was sane */
    if (epc < SOC_IROM_MASK_LOW || epc >= SOC_IROM_HIGH) {
        return;
    }
    volatile uint32_t* pepc = (uint32_t*)epc;

    panicPutStr("Memory dump at 0x");
    panicPutHex(epc);
    panicPutStr(": ");

    panicPutHex(*pepc);
    panicPutStr(" ");
    panicPutHex(*(pepc + 1));
    panicPutStr(" ");
    panicPutHex(*(pepc + 2));
    panicPutStr("\r\n");
}