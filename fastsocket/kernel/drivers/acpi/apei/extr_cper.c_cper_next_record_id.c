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
typedef  int u64 ;
typedef  int /*<<< orphan*/  atomic64_t ;

/* Variables and functions */
 int atomic64_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_seconds () ; 

u64 cper_next_record_id(void)
{
	static atomic64_t seq;

	if (!atomic64_read(&seq))
		atomic64_set(&seq, ((u64)get_seconds()) << 32);

	return atomic64_inc_return(&seq);
}