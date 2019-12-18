#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pt_regs {int dummy; } ;

/* Variables and functions */
#define  FP_CLS_INF 131 
#define  FP_CLS_NAN 130 
#define  FP_CLS_NORMAL 129 
#define  FP_CLS_ZERO 128 
 int /*<<< orphan*/  emu_set_CC (struct pt_regs*,int) ; 

__attribute__((used)) static inline void emu_set_CC_cs(struct pt_regs *regs, int class, int sign)
{
        switch (class) {
        case FP_CLS_NORMAL:
        case FP_CLS_INF:
                emu_set_CC(regs, sign ? 1 : 2);
                break;
        case FP_CLS_ZERO:
                emu_set_CC(regs, 0);
                break;
        case FP_CLS_NAN:
                emu_set_CC(regs, 3);
                break;
        }
}