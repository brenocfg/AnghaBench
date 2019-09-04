#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_5__ {TYPE_1__* affinity_set; } ;
struct TYPE_4__ {int /*<<< orphan*/  aset_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_AFFINITY_TAG_NULL ; 

uint32_t
thread_affinity_get(thread_t thread)
{
	uint32_t tag;

	if (thread->affinity_set != NULL)
		tag = thread->affinity_set->aset_tag;
	else
		tag = THREAD_AFFINITY_TAG_NULL;

	return tag;
}