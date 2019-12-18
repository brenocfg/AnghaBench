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
struct wait_bit_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_NORMAL ; 
 struct wait_bit_key __WAIT_BIT_KEY_INITIALIZER (void*,int) ; 
 int /*<<< orphan*/  __wake_up (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct wait_bit_key*) ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 

void __wake_up_bit(wait_queue_head_t *wq, void *word, int bit)
{
	struct wait_bit_key key = __WAIT_BIT_KEY_INITIALIZER(word, bit);
	if (waitqueue_active(wq))
		__wake_up(wq, TASK_NORMAL, 1, &key);
}