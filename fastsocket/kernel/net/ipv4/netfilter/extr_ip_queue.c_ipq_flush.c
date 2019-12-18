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
typedef  int /*<<< orphan*/  ipq_cmpfn ;

/* Variables and functions */
 int /*<<< orphan*/  __ipq_flush (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  queue_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipq_flush(ipq_cmpfn cmpfn, unsigned long data)
{
	write_lock_bh(&queue_lock);
	__ipq_flush(cmpfn, data);
	write_unlock_bh(&queue_lock);
}