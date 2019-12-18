#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  ilcs_mem_unlock; int /*<<< orphan*/  ilcs_mem_lock; int /*<<< orphan*/  ilcs_thread_init; int /*<<< orphan*/  ilcs_common_deinit; int /*<<< orphan*/  ilcs_common_init; int /*<<< orphan*/  fns; } ;
typedef  TYPE_1__ ILCS_CONFIG_T ;

/* Variables and functions */
 int /*<<< orphan*/  vcilcs_common_deinit ; 
 int /*<<< orphan*/  vcilcs_common_init ; 
 int /*<<< orphan*/  vcilcs_fns ; 
 int /*<<< orphan*/  vcilcs_mem_lock ; 
 int /*<<< orphan*/  vcilcs_mem_unlock ; 
 int /*<<< orphan*/  vcilcs_thread_init ; 

void vcilcs_config(ILCS_CONFIG_T *config)
{
   config->fns = vcilcs_fns;
   config->ilcs_common_init = vcilcs_common_init;
   config->ilcs_common_deinit = vcilcs_common_deinit;
   config->ilcs_thread_init = vcilcs_thread_init;
   config->ilcs_mem_lock = vcilcs_mem_lock;
   config->ilcs_mem_unlock = vcilcs_mem_unlock;
}