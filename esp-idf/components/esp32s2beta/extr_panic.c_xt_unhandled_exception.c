#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int exccause; int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ XtExcFrame ;

/* Variables and functions */
 int /*<<< orphan*/  APPTRACE_ONPANIC_HOST_FLUSH_TMO ; 
 int /*<<< orphan*/  CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_TRAX_THRESH ; 
 int /*<<< orphan*/  ESP_APPTRACE_DEST_TRAX ; 
 int NUM_EDESCS ; 
 int /*<<< orphan*/  SEGGER_RTT_ESP32_FlushNoLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort_called ; 
 int /*<<< orphan*/  commonErrorHandler (TYPE_1__*) ; 
 char** edesc ; 
 int /*<<< orphan*/  esp_apptrace_flush_nolock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_cpu_in_ocd_debug_mode () ; 
 int /*<<< orphan*/  haltOtherCore () ; 
 int /*<<< orphan*/  panicPutDec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panicPutHex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panicPutStr (char*) ; 
 int /*<<< orphan*/  setFirstBreakpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xPortGetCoreID () ; 

void xt_unhandled_exception(XtExcFrame *frame)
{
    haltOtherCore();
    if (!abort_called) {
        panicPutStr("Guru Meditation Error: Core ");
        panicPutDec(xPortGetCoreID());
        panicPutStr(" panic'ed (");
        int exccause = frame->exccause;
        if (exccause < NUM_EDESCS) {
            panicPutStr(edesc[exccause]);
        } else {
            panicPutStr("Unknown");
        }
        panicPutStr(")");
#ifdef PANIC_COMPLETE_IN_ESP32C
        if (esp_cpu_in_ocd_debug_mode()) {
            panicPutStr(" at pc=");
            panicPutHex(frame->pc);
            panicPutStr(". Setting bp and returning..\r\n");
#if CONFIG_ESP32_APPTRACE_ENABLE
#if CONFIG_SYSVIEW_ENABLE
            SEGGER_RTT_ESP32_FlushNoLock(CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_TRAX_THRESH, APPTRACE_ONPANIC_HOST_FLUSH_TMO);
#else
            esp_apptrace_flush_nolock(ESP_APPTRACE_DEST_TRAX, CONFIG_ESP32_APPTRACE_POSTMORTEM_FLUSH_TRAX_THRESH,
                                      APPTRACE_ONPANIC_HOST_FLUSH_TMO);
#endif
#endif
            //Stick a hardware breakpoint on the address the handler returns to. This way, the OCD debugger
            //will kick in exactly at the context the error happened.
            setFirstBreakpoint(frame->pc);
            return;
        }
#endif
        panicPutStr(". Exception was unhandled.\r\n");
    }
    commonErrorHandler(frame);
}