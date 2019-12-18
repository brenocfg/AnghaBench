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
struct TYPE_3__ {int head; int length; int /*<<< orphan*/  fillCount; } ;
typedef  TYPE_1__ TPCircularBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  OSAtomicAdd32Barrier (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ __attribute__((always_inline)) void TPCircularBufferProduce(TPCircularBuffer *buffer, int amount) {
    buffer->head = (buffer->head + amount) % buffer->length;
    OSAtomicAdd32Barrier(amount, &buffer->fillCount);
}