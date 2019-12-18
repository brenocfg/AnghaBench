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
struct TYPE_2__ {int /*<<< orphan*/  in_process_max; int /*<<< orphan*/  in_process; } ;
struct raid_set {TYPE_1__ io; } ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void io_get(struct raid_set *rs)
{
	int p = atomic_inc_return(&rs->io.in_process);

	if (p > atomic_read(&rs->io.in_process_max))
		atomic_set(&rs->io.in_process_max, p); /* REMOVEME: max. */
}