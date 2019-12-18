#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* type; } ;
struct TYPE_5__ {int kind; } ;
typedef  TYPE_2__ Operand ;

/* Variables and functions */
#define  TYPE_BOOL 134 
#define  TYPE_CHAR 133 
#define  TYPE_ENUM 132 
#define  TYPE_SCHAR 131 
#define  TYPE_SHORT 130 
#define  TYPE_UCHAR 129 
#define  TYPE_USHORT 128 
 int /*<<< orphan*/  cast_operand (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_int ; 

void promote_operand(Operand *operand) {
    switch (operand->type->kind) {
    case TYPE_BOOL:
    case TYPE_CHAR:
    case TYPE_SCHAR:
    case TYPE_UCHAR:
    case TYPE_SHORT:
    case TYPE_USHORT:
    case TYPE_ENUM:
        cast_operand(operand, type_int);
        break;
    default:
        // Do nothing
        break;
    }
}