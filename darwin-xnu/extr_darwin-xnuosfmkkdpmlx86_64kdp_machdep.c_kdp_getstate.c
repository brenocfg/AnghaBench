#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rsp; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;
typedef  TYPE_2__ x86_thread_state64_t ;
struct TYPE_6__ {int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rsp; } ;
struct TYPE_8__ {int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; TYPE_1__ isf; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
struct TYPE_9__ {scalar_t__ saved_state; } ;

/* Variables and functions */
 TYPE_5__ kdp ; 

void
kdp_getstate(
    x86_thread_state64_t	*state
)
{
    x86_saved_state64_t	*saved_state;
    
    saved_state = (x86_saved_state64_t *)kdp.saved_state;
    
    state->rax = saved_state->rax;
    state->rbx = saved_state->rbx;
    state->rcx = saved_state->rcx;
    state->rdx = saved_state->rdx;
    state->rdi = saved_state->rdi;
    state->rsi = saved_state->rsi;
    state->rbp = saved_state->rbp;

    state->r8  = saved_state->r8;
    state->r9  = saved_state->r9;
    state->r10 = saved_state->r10;
    state->r11 = saved_state->r11;
    state->r12 = saved_state->r12;
    state->r13 = saved_state->r13;
    state->r14 = saved_state->r14;
    state->r15 = saved_state->r15;
    
    state->rsp = saved_state->isf.rsp;
    state->rflags = saved_state->isf.rflags;
    state->rip = saved_state->isf.rip;

    state->cs = saved_state->isf.cs;
    state->fs = saved_state->fs;
    state->gs = saved_state->gs;
}