#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BUF_FREE_HEX ; 
 uintptr_t KERN_CONSOLE_BUF_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ console_ring ; 

void
console_cpu_free(void * buf)
{
	assert((uintptr_t)buf > (uintptr_t)console_ring.buffer);
	assert((uintptr_t)buf < (uintptr_t)console_ring.buffer + KERN_CONSOLE_BUF_SIZE);
	if (buf != NULL)
		*(uint32_t *)buf = CPU_BUF_FREE_HEX;
}