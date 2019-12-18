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

/* Variables and functions */
 int __ipq_set_mode (unsigned char,unsigned int) ; 
 int /*<<< orphan*/  queue_lock ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ipq_set_mode(unsigned char mode, unsigned int range)
{
	int status;

	write_lock_bh(&queue_lock);
	status = __ipq_set_mode(mode, range);
	write_unlock_bh(&queue_lock);
	return status;
}