#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  MemorySize; scalar_t__ tasks; } ;
typedef  TYPE_1__* PISDN_ADAPTER ;

/* Variables and functions */
 scalar_t__ MQ_INSTANCE_COUNT ; 
 int /*<<< orphan*/  MQ_MEMORY_SIZE ; 
 int /*<<< orphan*/  diva_os_set_qBri_functions (TYPE_1__*) ; 
 int /*<<< orphan*/  set_common_qBri_functions (TYPE_1__*) ; 

__attribute__((used)) static void set_qBri_functions (PISDN_ADAPTER IoAdapter) {
	if (!IoAdapter->tasks) {
		IoAdapter->tasks = MQ_INSTANCE_COUNT;
	}
	IoAdapter->MemorySize = MQ_MEMORY_SIZE ;
	set_common_qBri_functions (IoAdapter) ;
	diva_os_set_qBri_functions (IoAdapter) ;
}