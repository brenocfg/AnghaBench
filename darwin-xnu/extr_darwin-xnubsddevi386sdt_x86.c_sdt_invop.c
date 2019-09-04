#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  r8; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; } ;
typedef  TYPE_1__ x86_saved_state64_t ;
struct TYPE_5__ {int /*<<< orphan*/  sdp_id; scalar_t__ sdp_patchpoint; struct TYPE_5__* sdp_hashnext; } ;
typedef  TYPE_2__ sdt_probe_t ;

/* Variables and functions */
 int DTRACE_INVOP_NOP ; 
 size_t SDT_ADDR2NDX (uintptr_t) ; 
 int /*<<< orphan*/  dtrace_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__** sdt_probetab ; 

int
sdt_invop(uintptr_t addr, uintptr_t *stack, uintptr_t eax)
{
#pragma unused(eax)
	sdt_probe_t *sdt = sdt_probetab[SDT_ADDR2NDX(addr)];

	for (; sdt != NULL; sdt = sdt->sdp_hashnext) {
		if ((uintptr_t)sdt->sdp_patchpoint == addr) {
			x86_saved_state64_t *regs = (x86_saved_state64_t *)stack;

			dtrace_probe(sdt->sdp_id, regs->rdi, regs->rsi, regs->rdx, regs->rcx, regs->r8);

			return (DTRACE_INVOP_NOP);
		}
	}

	return (0);
}