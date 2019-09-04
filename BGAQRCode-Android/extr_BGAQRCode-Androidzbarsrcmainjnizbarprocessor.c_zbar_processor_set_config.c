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
typedef  int /*<<< orphan*/  zbar_symbol_type_t ;
struct TYPE_5__ {int /*<<< orphan*/  scanner; } ;
typedef  TYPE_1__ zbar_processor_t ;
typedef  int /*<<< orphan*/  zbar_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_leave (TYPE_1__*) ; 
 int zbar_image_scanner_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int zbar_processor_set_config (zbar_processor_t *proc,
                               zbar_symbol_type_t sym,
                               zbar_config_t cfg,
                               int val)
{
    proc_enter(proc);
    int rc = zbar_image_scanner_set_config(proc->scanner, sym, cfg, val);
    proc_leave(proc);
    return(rc);
}