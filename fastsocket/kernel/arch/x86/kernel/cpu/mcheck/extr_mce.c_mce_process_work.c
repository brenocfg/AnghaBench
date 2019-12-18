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
 int /*<<< orphan*/  MCE_VECTOR ; 
 scalar_t__ mce_ring_get (unsigned long*) ; 
 int /*<<< orphan*/  memory_failure (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mce_process_work(struct work_struct *dummy)
{
	unsigned long pfn;

	while (mce_ring_get(&pfn))
		memory_failure(pfn, MCE_VECTOR, 0);
}