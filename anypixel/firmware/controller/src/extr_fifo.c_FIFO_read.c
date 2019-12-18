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
struct TYPE_3__ {int size; int free; scalar_t__ tail; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ FIFO_Data_TypeDef ;

/* Variables and functions */
 int __LDREXH (int*) ; 
 scalar_t__ __STREXH (int,int*) ; 

bool FIFO_read(FIFO_Data_TypeDef *inStruct, uint8_t *outByte, uint16_t count) {
	int i;
	uint16_t workFree;

	if( count > (inStruct->size - inStruct->free) )
		return false;

	for(i = 0; i < count; i++) {
		outByte[i] = inStruct->buffer[inStruct->tail++];
		if(inStruct->tail >= inStruct->size) {
			inStruct->tail = 0;
		}
	}
    do {
        workFree = __LDREXH(&inStruct->free);
        workFree += count;
    } while( __STREXH(workFree, &inStruct->free));

	return true;
}