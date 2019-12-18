#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_head_t ;
typedef  void atomic_t ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 int /*<<< orphan*/ * bit_waitqueue (void*,unsigned long) ; 

__attribute__((used)) static inline wait_queue_head_t *atomic_t_waitqueue(atomic_t *p)
{
	if (BITS_PER_LONG == 64) {
		unsigned long q = (unsigned long)p;
		return bit_waitqueue((void *)(q & ~1), q & 1);
	}
	return bit_waitqueue(p, 0);
}