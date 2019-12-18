#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t exccause; int /*<<< orphan*/  pc; } ;
typedef  TYPE_2__ XtExcFrame ;
struct TYPE_7__ {int wdt; } ;
struct TYPE_9__ {TYPE_1__ int_clr; } ;

/* Variables and functions */
 int /*<<< orphan*/  APPTRACE_ONPANIC_HOST_FLUSH_TMO ; 
 int /*<<< orphan*/  CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_TRAX_THRESH ; 
 int /*<<< orphan*/  ESP_APPTRACE_DEST_TRAX ; 
 size_t PANIC_RSN_CACHEERR ; 
 size_t PANIC_RSN_DEBUGEXCEPTION ; 
 size_t PANIC_RSN_INTWDT_CPU0 ; 
 size_t PANIC_RSN_INTWDT_CPU1 ; 
 size_t PANIC_RSN_MAX ; 
 int /*<<< orphan*/  SEGGER_RTT_ESP32_FlushNoLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ TIMERG1 ; 
 int XCHAL_DEBUGCAUSE_BREAKN_MASK ; 
 int XCHAL_DEBUGCAUSE_BREAK_MASK ; 
 int XCHAL_DEBUGCAUSE_DBREAK_MASK ; 
 int XCHAL_DEBUGCAUSE_DEBUGINT_MASK ; 
 int XCHAL_DEBUGCAUSE_IBREAK_MASK ; 
 int XCHAL_DEBUGCAUSE_ICOUNT_MASK ; 
 int /*<<< orphan*/  commonErrorHandler (TYPE_2__*) ; 
 int /*<<< orphan*/  disableAllWdts () ; 
 int /*<<< orphan*/  esp_apptrace_flush_nolock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int esp_cache_err_get_cpuid () ; 
 scalar_t__ esp_cpu_in_ocd_debug_mode () ; 
 int /*<<< orphan*/  ets_delay_us (int) ; 
 int /*<<< orphan*/  haltOtherCore () ; 
 TYPE_2__* other_core_frame ; 
 int /*<<< orphan*/  panicPutDec (int) ; 
 int /*<<< orphan*/  panicPutStr (char const*) ; 
 char* pcTaskGetTaskName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printCacheError () ; 
 int /*<<< orphan*/  setFirstBreakpoint (int /*<<< orphan*/ ) ; 
 int xPortGetCoreID () ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandleForCPU (int) ; 

void panicHandler(XtExcFrame *frame)
{
    int core_id = xPortGetCoreID();
    //Please keep in sync with PANIC_RSN_* defines
    const char *reasons[] = {
        "Unknown reason",
        "Unhandled debug exception",
        "Double exception",
        "Unhandled kernel exception",
        "Coprocessor exception",
        "Interrupt wdt timeout on CPU0",
        "Interrupt wdt timeout on CPU1",
        "Cache exception",
    };
    const char *reason = reasons[0];
    //The panic reason is stored in the EXCCAUSE register.
    if (frame->exccause <= PANIC_RSN_MAX) {
        reason = reasons[frame->exccause];
    }

#if !CONFIG_FREERTOS_UNICORE
    //Save frame for other core.
    if ((frame->exccause == PANIC_RSN_INTWDT_CPU0 && core_id == 1) || (frame->exccause == PANIC_RSN_INTWDT_CPU1 && core_id == 0)) {
        other_core_frame = frame;
        while (1);
    }

    //The core which triggers the interrupt watchdog will delay 1 us, so the other core can save its frame.
    if (frame->exccause == PANIC_RSN_INTWDT_CPU0 || frame->exccause == PANIC_RSN_INTWDT_CPU1) {
        ets_delay_us(1);
    }

    if (frame->exccause == PANIC_RSN_CACHEERR && esp_cache_err_get_cpuid() != core_id) {
        // Cache error interrupt will be handled by the panic handler
        // on the other CPU.
        while (1);
    }
#endif //!CONFIG_FREERTOS_UNICORE

    haltOtherCore();
    panicPutStr("Guru Meditation Error: Core ");
    panicPutDec(core_id);
    panicPutStr(" panic'ed (");
    panicPutStr(reason);
    panicPutStr(")\r\n");
    if (frame->exccause == PANIC_RSN_DEBUGEXCEPTION) {
        int debugRsn;
        asm("rsr.debugcause %0":"=r"(debugRsn));
        panicPutStr("Debug exception reason: ");
        if (debugRsn & XCHAL_DEBUGCAUSE_ICOUNT_MASK) {
            panicPutStr("SingleStep ");
        }
        if (debugRsn & XCHAL_DEBUGCAUSE_IBREAK_MASK) {
            panicPutStr("HwBreakpoint ");
        }
        if (debugRsn & XCHAL_DEBUGCAUSE_DBREAK_MASK) {
            //Unlike what the ISA manual says, this core seemingly distinguishes from a DBREAK
            //reason caused by watchdog 0 and one caused by watchdog 1 by setting bit 8 of the
            //debugcause if the cause is watchdog 1 and clearing it if it's watchdog 0.
            if (debugRsn & (1 << 8)) {
#if CONFIG_FREERTOS_WATCHPOINT_END_OF_STACK
                const char *name = pcTaskGetTaskName(xTaskGetCurrentTaskHandleForCPU(core_id));
                panicPutStr("Stack canary watchpoint triggered (");
                panicPutStr(name);
                panicPutStr(") ");
#else
                panicPutStr("Watchpoint 1 triggered ");
#endif
            } else {
                panicPutStr("Watchpoint 0 triggered ");
            }
        }
        if (debugRsn & XCHAL_DEBUGCAUSE_BREAK_MASK) {
            panicPutStr("BREAK instr ");
        }
        if (debugRsn & XCHAL_DEBUGCAUSE_BREAKN_MASK) {
            panicPutStr("BREAKN instr ");
        }
        if (debugRsn & XCHAL_DEBUGCAUSE_DEBUGINT_MASK) {
            panicPutStr("DebugIntr ");
        }
        panicPutStr("\r\n");
    } else if (frame->exccause == PANIC_RSN_CACHEERR) {
        panicPutStr("                                         ^~~~~~~~~~~~~~~\r\n");
        printCacheError();
    }

    if (esp_cpu_in_ocd_debug_mode()) {
        disableAllWdts();
        if (frame->exccause == PANIC_RSN_INTWDT_CPU0 ||
            frame->exccause == PANIC_RSN_INTWDT_CPU1) {
            TIMERG1.int_clr.wdt = 1;
        }
#if CONFIG_ESP32_APPTRACE_ENABLE
#if CONFIG_SYSVIEW_ENABLE
        SEGGER_RTT_ESP32_FlushNoLock(CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_TRAX_THRESH, APPTRACE_ONPANIC_HOST_FLUSH_TMO);
#else
        esp_apptrace_flush_nolock(ESP_APPTRACE_DEST_TRAX, CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_TRAX_THRESH,
                                  APPTRACE_ONPANIC_HOST_FLUSH_TMO);
#endif
#endif
        setFirstBreakpoint(frame->pc);
        return;
    }
    commonErrorHandler(frame);
}