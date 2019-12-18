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
struct TYPE_5__ {int /*<<< orphan*/  MemorySize; } ;
typedef  TYPE_1__* PISDN_ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  MP_MEMORY_SIZE ; 
 int /*<<< orphan*/  diva_os_prepare_pri_functions (TYPE_1__*) ; 
 int /*<<< orphan*/  prepare_common_pri_functions (TYPE_1__*) ; 

void prepare_pri_functions (PISDN_ADAPTER IoAdapter) {
 IoAdapter->MemorySize = MP_MEMORY_SIZE ;
 prepare_common_pri_functions (IoAdapter) ;
 diva_os_prepare_pri_functions (IoAdapter);
}