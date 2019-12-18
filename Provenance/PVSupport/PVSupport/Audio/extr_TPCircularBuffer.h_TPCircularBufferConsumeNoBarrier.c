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
typedef  int int32_t ;
struct TYPE_3__ {int tail; int length; int fillCount; } ;
typedef  TYPE_1__ TPCircularBuffer ;

/* Variables and functions */

__attribute__((used)) static __inline__ __attribute__((always_inline)) void TPCircularBufferConsumeNoBarrier(TPCircularBuffer *buffer, int32_t amount) {
    buffer->tail = (buffer->tail + amount) % buffer->length;
    buffer->fillCount -= amount;
}