#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Operand ;

/* Variables and functions */
 int is_scalar_type (int /*<<< orphan*/ ) ; 
 TYPE_1__ operand_decay (TYPE_1__) ; 

bool is_cond_operand(Operand operand) {
    operand = operand_decay(operand);
    return is_scalar_type(operand.type);
}