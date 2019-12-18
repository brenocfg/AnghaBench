#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pc_maint {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  ram_inc; int /*<<< orphan*/  ram_out_buffer; int /*<<< orphan*/  ram_outw; int /*<<< orphan*/  ram_out; int /*<<< orphan*/  ram_look_ahead; int /*<<< orphan*/  ram_in_buffer; int /*<<< orphan*/  ram_inw; int /*<<< orphan*/  ram_in; } ;
struct TYPE_5__ {int /*<<< orphan*/  diva_isr_handler; int /*<<< orphan*/  trapFnc; int /*<<< orphan*/  stop; int /*<<< orphan*/  rstFnc; int /*<<< orphan*/  disIrq; int /*<<< orphan*/  load; struct pc_maint* pcm; int /*<<< orphan*/  clr_irq; int /*<<< orphan*/  tst_irq; int /*<<< orphan*/  dpc; int /*<<< orphan*/  out; int /*<<< orphan*/  MemorySize; int /*<<< orphan*/  MemoryBase; TYPE_2__ a; } ;
typedef  TYPE_1__* PISDN_ADAPTER ;
typedef  TYPE_2__ ADAPTER ;

/* Variables and functions */
 int /*<<< orphan*/  BRI_MEMORY_BASE ; 
 int /*<<< orphan*/  BRI_MEMORY_SIZE ; 
 scalar_t__ MIPS_MAINT_OFFS ; 
 int /*<<< orphan*/  bri_ISR ; 
 int /*<<< orphan*/  bri_cpu_trapped ; 
 int /*<<< orphan*/  disable_bri_interrupt ; 
 int /*<<< orphan*/  diva_os_prepare_maestra_functions (TYPE_1__*) ; 
 int /*<<< orphan*/  io_in ; 
 int /*<<< orphan*/  io_in_buffer ; 
 int /*<<< orphan*/  io_inc ; 
 int /*<<< orphan*/  io_inw ; 
 int /*<<< orphan*/  io_look_ahead ; 
 int /*<<< orphan*/  io_out ; 
 int /*<<< orphan*/  io_out_buffer ; 
 int /*<<< orphan*/  io_outw ; 
 int /*<<< orphan*/  load_bri_hardware ; 
 int /*<<< orphan*/  pr_dpc ; 
 int /*<<< orphan*/  pr_out ; 
 int /*<<< orphan*/  reset_bri_hardware ; 
 int /*<<< orphan*/  scom_clear_int ; 
 int /*<<< orphan*/  scom_test_int ; 
 int /*<<< orphan*/  stop_bri_hardware ; 

void prepare_maestra_functions (PISDN_ADAPTER IoAdapter) {
 ADAPTER *a = &IoAdapter->a ;
 a->ram_in             = io_in ;
 a->ram_inw            = io_inw ;
 a->ram_in_buffer      = io_in_buffer ;
 a->ram_look_ahead     = io_look_ahead ;
 a->ram_out            = io_out ;
 a->ram_outw           = io_outw ;
 a->ram_out_buffer     = io_out_buffer ;
 a->ram_inc            = io_inc ;
 IoAdapter->MemoryBase = BRI_MEMORY_BASE ;
 IoAdapter->MemorySize = BRI_MEMORY_SIZE ;
 IoAdapter->out        = pr_out ;
 IoAdapter->dpc        = pr_dpc ;
 IoAdapter->tst_irq    = scom_test_int ;
 IoAdapter->clr_irq    = scom_clear_int ;
 IoAdapter->pcm        = (struct pc_maint *)MIPS_MAINT_OFFS ;
 IoAdapter->load       = load_bri_hardware ;
 IoAdapter->disIrq     = disable_bri_interrupt ;
 IoAdapter->rstFnc     = reset_bri_hardware ;
 IoAdapter->stop       = stop_bri_hardware ;
 IoAdapter->trapFnc    = bri_cpu_trapped ;
 IoAdapter->diva_isr_handler = bri_ISR;
 /*
  Prepare OS dependent functions
  */
 diva_os_prepare_maestra_functions (IoAdapter);
}