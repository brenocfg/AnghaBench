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
typedef  int /*<<< orphan*/  zbar_symbol_set_t ;
struct TYPE_5__ {int /*<<< orphan*/ * syms; } ;
typedef  TYPE_1__ zbar_processor_t ;

/* Variables and functions */
 int /*<<< orphan*/  proc_enter (TYPE_1__*) ; 
 int /*<<< orphan*/  proc_leave (TYPE_1__*) ; 
 int /*<<< orphan*/  zbar_symbol_set_ref (int /*<<< orphan*/  const*,int) ; 

const zbar_symbol_set_t*
zbar_processor_get_results (const zbar_processor_t *proc)
{
    zbar_processor_t *ncproc = (zbar_processor_t*)proc;
    proc_enter(ncproc);
    const zbar_symbol_set_t *syms = proc->syms;
    if(syms)
        zbar_symbol_set_ref(syms, 1);
    proc_leave(ncproc);
    return(syms);
}