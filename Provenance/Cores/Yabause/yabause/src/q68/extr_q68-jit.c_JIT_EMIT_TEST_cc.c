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
typedef  int /*<<< orphan*/  Q68JitEntry ;

/* Variables and functions */
#define  COND_CC 143 
#define  COND_CS 142 
#define  COND_EQ 141 
#define  COND_F 140 
#define  COND_GE 139 
#define  COND_GT 138 
#define  COND_HI 137 
#define  COND_LE 136 
#define  COND_LS 135 
#define  COND_LT 134 
#define  COND_MI 133 
#define  COND_NE 132 
#define  COND_PL 131 
#define  COND_T 130 
#define  COND_VC 129 
#define  COND_VS 128 
 int /*<<< orphan*/  JIT_EMIT_TEST_CC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_CS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_EQ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_F (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_GE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_GT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_HI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_LE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_LS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_LT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_MI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_NE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_PL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_T (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_VC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_TEST_VS (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void JIT_EMIT_TEST_cc(int cond, Q68JitEntry *entry)
{
    switch ((cond)) {
        case COND_T:  JIT_EMIT_TEST_T (entry); break;
        case COND_F:  JIT_EMIT_TEST_F (entry); break;
        case COND_HI: JIT_EMIT_TEST_HI(entry); break;
        case COND_LS: JIT_EMIT_TEST_LS(entry); break;
        case COND_CC: JIT_EMIT_TEST_CC(entry); break;
        case COND_CS: JIT_EMIT_TEST_CS(entry); break;
        case COND_NE: JIT_EMIT_TEST_NE(entry); break;
        case COND_EQ: JIT_EMIT_TEST_EQ(entry); break;
        case COND_VC: JIT_EMIT_TEST_VC(entry); break;
        case COND_VS: JIT_EMIT_TEST_VS(entry); break;
        case COND_PL: JIT_EMIT_TEST_PL(entry); break;
        case COND_MI: JIT_EMIT_TEST_MI(entry); break;
        case COND_GE: JIT_EMIT_TEST_GE(entry); break;
        case COND_LT: JIT_EMIT_TEST_LT(entry); break;
        case COND_GT: JIT_EMIT_TEST_GT(entry); break;
        case COND_LE: JIT_EMIT_TEST_LE(entry); break;
    }
}