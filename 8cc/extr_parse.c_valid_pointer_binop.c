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

/* Variables and functions */
#define  OP_EQ 131 
#define  OP_GE 130 
#define  OP_LE 129 
#define  OP_NE 128 

__attribute__((used)) static bool valid_pointer_binop(int op) {
    switch (op) {
    case '-': case '<': case '>': case OP_EQ:
    case OP_NE: case OP_GE: case OP_LE:
        return true;
    default:
        return false;
    }
}