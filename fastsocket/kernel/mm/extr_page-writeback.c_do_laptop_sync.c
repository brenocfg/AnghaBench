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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct work_struct*) ; 
 int /*<<< orphan*/  wakeup_flusher_threads (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_laptop_sync(struct work_struct *work)
{
	wakeup_flusher_threads(0);
	kfree(work);
}