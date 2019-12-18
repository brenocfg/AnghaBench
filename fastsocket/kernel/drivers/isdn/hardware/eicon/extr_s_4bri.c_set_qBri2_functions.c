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
struct TYPE_5__ {int tasks; int /*<<< orphan*/  MemorySize; } ;
typedef  TYPE_1__* PISDN_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  BRI2_MEMORY_SIZE ; 
 int /*<<< orphan*/  MQ2_MEMORY_SIZE ; 
 int MQ_INSTANCE_COUNT ; 
 int /*<<< orphan*/  diva_os_set_qBri2_functions (TYPE_1__*) ; 
 int /*<<< orphan*/  set_common_qBri_functions (TYPE_1__*) ; 

__attribute__((used)) static void set_qBri2_functions (PISDN_ADAPTER IoAdapter) {
	if (!IoAdapter->tasks) {
		IoAdapter->tasks = MQ_INSTANCE_COUNT;
	}
	IoAdapter->MemorySize = (IoAdapter->tasks == 1) ? BRI2_MEMORY_SIZE : MQ2_MEMORY_SIZE;
	set_common_qBri_functions (IoAdapter) ;
	diva_os_set_qBri2_functions (IoAdapter) ;
}