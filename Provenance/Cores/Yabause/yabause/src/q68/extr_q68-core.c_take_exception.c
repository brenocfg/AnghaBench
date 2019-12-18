#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int const uint8_t ;
struct TYPE_7__ {int SR; int USP; int* A; int SSP; int PC; int fault_opcode; int fault_addr; int fault_status; void* halted; int /*<<< orphan*/ * jit_running; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
#define  EX_ADDRESS_ERROR 146 
#define  EX_BUS_ERROR 145 
#define  EX_CHK 144 
#define  EX_DIVIDE_BY_ZERO 143 
#define  EX_ILLEGAL_INSTRUCTION 142 
#define  EX_LEVEL_1_INTERRUPT 141 
#define  EX_LEVEL_2_INTERRUPT 140 
#define  EX_LEVEL_3_INTERRUPT 139 
#define  EX_LEVEL_4_INTERRUPT 138 
#define  EX_LEVEL_5_INTERRUPT 137 
#define  EX_LEVEL_6_INTERRUPT 136 
#define  EX_LEVEL_7_INTERRUPT 135 
#define  EX_LINE_1010 134 
#define  EX_LINE_1111 133 
#define  EX_PRIVILEGE_VIOLATION 132 
#define  EX_SPURIOUS_INTERRUPT 131 
#define  EX_TRACE 130 
#define  EX_TRAP 129 
#define  EX_TRAPV 128 
 int /*<<< orphan*/  PUSH16 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  PUSH32 (TYPE_1__*,int) ; 
 void* Q68_HALTED_DOUBLE_FAULT ; 
 int READU32 (TYPE_1__*,int const) ; 
 int SR_S ; 
 int /*<<< orphan*/  SR_SET_I (TYPE_1__*,int const) ; 

__attribute__((used)) static int take_exception(Q68State *state, uint8_t num)
{
    static const int exception_cycles[256] = {
        [EX_BUS_ERROR                ] = 50,
        [EX_ADDRESS_ERROR            ] = 50,
        [EX_ILLEGAL_INSTRUCTION      ] = 34,
        [EX_DIVIDE_BY_ZERO           ] = 42,
        [EX_CHK                      ] = 44,
        [EX_TRAPV                    ] = 34,
        [EX_PRIVILEGE_VIOLATION      ] = 34,
        [EX_TRACE                    ] = 34,
        [EX_LINE_1010                ] = 34,  // These two are assumed to be
        [EX_LINE_1111                ] = 34,  // equal to ILLEGAL_INSTRUCTION
        [EX_SPURIOUS_INTERRUPT       ] = 44,
        [EX_LEVEL_1_INTERRUPT        ] = 44,
        [EX_LEVEL_2_INTERRUPT        ] = 44,
        [EX_LEVEL_3_INTERRUPT        ] = 44,
        [EX_LEVEL_4_INTERRUPT        ] = 44,
        [EX_LEVEL_5_INTERRUPT        ] = 44,
        [EX_LEVEL_6_INTERRUPT        ] = 44,
        [EX_LEVEL_7_INTERRUPT        ] = 44,
        [EX_TRAP+ 0                  ] = 38,
        [EX_TRAP+ 1                  ] = 38,
        [EX_TRAP+ 2                  ] = 38,
        [EX_TRAP+ 3                  ] = 38,
        [EX_TRAP+ 4                  ] = 38,
        [EX_TRAP+ 5                  ] = 38,
        [EX_TRAP+ 6                  ] = 38,
        [EX_TRAP+ 7                  ] = 38,
        [EX_TRAP+ 8                  ] = 38,
        [EX_TRAP+ 9                  ] = 38,
        [EX_TRAP+10                  ] = 38,
        [EX_TRAP+11                  ] = 38,
        [EX_TRAP+12                  ] = 38,
        [EX_TRAP+13                  ] = 38,
        [EX_TRAP+14                  ] = 38,
        [EX_TRAP+15                  ] = 38,
    };

    /* Clear this out ahead of time in case we hit a double fault */
    state->jit_running = NULL;

    if (!(state->SR & SR_S)) {
        state->USP = state->A[7];
        state->A[7] = state->SSP;
    }
#ifndef Q68_DISABLE_ADDRESS_ERROR
    if (state->A[7] & 1) {
        state->halted = Q68_HALTED_DOUBLE_FAULT;  // Oops!
        return 0;
    }
#endif
    PUSH32(state, state->PC);
    PUSH16(state, state->SR);
    if (num == EX_BUS_ERROR || num == EX_ADDRESS_ERROR) {
        PUSH16(state, state->fault_opcode);
        PUSH32(state, state->fault_addr);
        PUSH16(state, state->fault_status);
    }
    state->SR |= SR_S;
    if (num >= EX_LEVEL_1_INTERRUPT && num <= EX_LEVEL_7_INTERRUPT) {
        SR_SET_I(state, (num - EX_LEVEL_1_INTERRUPT) + 1);
    }
    state->PC = READU32(state, num*4);
#ifndef Q68_DISABLE_ADDRESS_ERROR
    if (state->PC & 1) {
        /* FIXME: Does a real 68000 double fault here or just take an
         * address error exception? */
        state->halted = Q68_HALTED_DOUBLE_FAULT;
        return 0;
    }
#endif
    return exception_cycles[num];
}