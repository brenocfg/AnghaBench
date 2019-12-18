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
struct TYPE_4__ {int kind; } ;
typedef  TYPE_1__ Type ;
struct TYPE_5__ {int sign; } ;

/* Variables and functions */
#define  TYPE_CHAR 133 
#define  TYPE_INT 132 
#define  TYPE_LLONG 131 
#define  TYPE_LONG 130 
#define  TYPE_SCHAR 129 
#define  TYPE_SHORT 128 
 TYPE_2__* type_metrics ; 

bool is_signed_type(Type *type) {
    switch (type->kind) {
    case TYPE_CHAR:
        return type_metrics[TYPE_CHAR].sign;
    case TYPE_SCHAR:
    case TYPE_SHORT:
    case TYPE_INT:
    case TYPE_LONG:
    case TYPE_LLONG:
        return true;
    default:
        return false;
    }
}