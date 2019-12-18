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
struct request_queue {int /*<<< orphan*/  queue_flags; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_UNPRIV_SGIO ; 
 int /*<<< orphan*/  queue_var_show (int,char*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
queue_show_unpriv_sgio(struct request_queue *q, char *page)
{
	int bit;
	bit = test_bit(QUEUE_FLAG_UNPRIV_SGIO, &q->queue_flags);
	return queue_var_show(bit, page);
}