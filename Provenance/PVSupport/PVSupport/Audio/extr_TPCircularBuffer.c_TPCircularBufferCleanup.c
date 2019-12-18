#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_address_t ;
struct TYPE_4__ {int length; scalar_t__ buffer; } ;
typedef  TYPE_1__ TPCircularBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_deallocate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void TPCircularBufferCleanup(TPCircularBuffer *buffer) {
    vm_deallocate(mach_task_self(), (vm_address_t)buffer->buffer, buffer->length * 2);
    memset(buffer, 0, sizeof(TPCircularBuffer));
}