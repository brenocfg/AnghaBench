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
typedef  void* uint16_t ;
struct TYPE_3__ {scalar_t__ overrun; void* free; void* size; scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_1__ FIFO_Data_TypeDef ;

/* Variables and functions */

bool FIFO_InitStruct(FIFO_Data_TypeDef *inStruct, uint8_t* inBuf, uint16_t inBufSize) {
	if(inStruct == NULL || inBuf == NULL)
		return false;
	inStruct->buffer = inBuf;
	inStruct->head = 0;
	inStruct->tail = 0;
	inStruct->size = inBufSize;
	inStruct->free = inBufSize;
	inStruct->overrun = 0;
	return true;
}