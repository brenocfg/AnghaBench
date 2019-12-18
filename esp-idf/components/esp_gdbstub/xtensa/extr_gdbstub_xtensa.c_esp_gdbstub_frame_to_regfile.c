#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int pc; int* a; int ps; int /*<<< orphan*/  sar; int /*<<< orphan*/  lcount; int /*<<< orphan*/  lend; int /*<<< orphan*/  lbeg; } ;
typedef  TYPE_1__ esp_gdbstub_gdb_regfile_t ;
struct TYPE_8__ {int pc; int ps; int /*<<< orphan*/  sar; int /*<<< orphan*/  lcount; int /*<<< orphan*/  lend; int /*<<< orphan*/  lbeg; int /*<<< orphan*/  a0; } ;
typedef  TYPE_2__ esp_gdbstub_frame_t ;

/* Variables and functions */
 int PS_EXCM ; 
 int PS_UM ; 
 int /*<<< orphan*/  init_regfile (TYPE_1__*) ; 
 int /*<<< orphan*/  update_regfile_common (TYPE_1__*) ; 

void esp_gdbstub_frame_to_regfile(const esp_gdbstub_frame_t *frame, esp_gdbstub_gdb_regfile_t *dst)
{
    init_regfile(dst);
    const uint32_t *a_regs = (const uint32_t *) &frame->a0;
    dst->pc = (frame->pc & 0x3fffffffU) | 0x40000000U;

    for (int i = 0; i < 16; i++) {
        dst->a[i] = a_regs[i];
    }
    for (int i = 16; i < 64; i++) {
        dst->a[i] = 0xDEADBEEF;
    }

#if XCHAL_HAVE_LOOPS
    dst->lbeg = frame->lbeg;
    dst->lend = frame->lend;
    dst->lcount = frame->lcount;
#endif

    dst->ps = (frame->ps & PS_UM) ? (frame->ps & ~PS_EXCM) : frame->ps;
    dst->sar = frame->sar;
    update_regfile_common(dst);
}