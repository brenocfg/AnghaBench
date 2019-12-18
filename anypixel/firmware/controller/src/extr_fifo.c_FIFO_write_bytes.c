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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct TYPE_3__ {int free; scalar_t__ head; scalar_t__ size; int /*<<< orphan*/ * buffer; int /*<<< orphan*/  overrun; } ;
typedef  TYPE_1__ FIFO_Data_TypeDef ;

/* Variables and functions */
 int __LDREXH (int*) ; 
 scalar_t__ __STREXH (int,int*) ; 

bool FIFO_write_bytes(FIFO_Data_TypeDef *inStruct, uint8_t *inBytes, uint16_t count) {
	int i;
	uint16_t workFree;

	if(inStruct->free < count) {
		inStruct->overrun++;
		return false;
	}

    for(i = 0; i < count; i++) {
        inStruct->buffer[inStruct->head++] = inBytes[i];
        if(inStruct->head >= inStruct->size)
            inStruct->head = 0;
    }
    do {
        workFree = __LDREXH(&inStruct->free);
        workFree -= count;
    } while( __STREXH(workFree, &inStruct->free));

	return true;
}