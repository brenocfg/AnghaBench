#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kind; int id; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
#define  OP_A_ADD 138 
#define  OP_A_AND 137 
#define  OP_A_DIV 136 
#define  OP_A_MOD 135 
#define  OP_A_MUL 134 
#define  OP_A_OR 133 
#define  OP_A_SAL 132 
#define  OP_A_SAR 131 
#define  OP_A_SHR 130 
#define  OP_A_SUB 129 
#define  OP_A_XOR 128 
 int OP_SAL ; 
 int OP_SAR ; 
 int OP_SHR ; 
 scalar_t__ TKEYWORD ; 

__attribute__((used)) static int get_compound_assign_op(Token *tok) {
    if (tok->kind != TKEYWORD)
        return 0;
    switch (tok->id) {
    case OP_A_ADD: return '+';
    case OP_A_SUB: return '-';
    case OP_A_MUL: return '*';
    case OP_A_DIV: return '/';
    case OP_A_MOD: return '%';
    case OP_A_AND: return '&';
    case OP_A_OR:  return '|';
    case OP_A_XOR: return '^';
    case OP_A_SAL: return OP_SAL;
    case OP_A_SAR: return OP_SAR;
    case OP_A_SHR: return OP_SHR;
    default: return 0;
    }
}