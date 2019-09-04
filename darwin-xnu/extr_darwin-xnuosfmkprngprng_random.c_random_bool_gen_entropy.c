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
struct bool_gen {int* seed; int state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
random_bool_gen_entropy(struct bool_gen * bg, unsigned int * buffer, int count)
{
	simple_lock(&bg->lock);
	int i, t;
	for (i = 0; i < count; i++) {
		bg->seed[1] ^= (bg->seed[1] << 5);
		bg->seed[1] ^= (bg->seed[1] >> 7);
		bg->seed[1] ^= (bg->seed[1] << 22);
		t           = bg->seed[2] + bg->seed[3] + bg->state;
		bg->seed[2] = bg->seed[3];
		bg->state   = t < 0;
		bg->seed[3] = t & 2147483647;
		bg->seed[0] += 1411392427;
		buffer[i] = (bg->seed[0] + bg->seed[1] + bg->seed[3]);
	}
	simple_unlock(&bg->lock);
}