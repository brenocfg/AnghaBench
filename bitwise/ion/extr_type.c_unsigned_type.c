#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int kind; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
#define  TYPE_BOOL 139 
#define  TYPE_CHAR 138 
#define  TYPE_INT 137 
#define  TYPE_LLONG 136 
#define  TYPE_LONG 135 
#define  TYPE_SCHAR 134 
#define  TYPE_SHORT 133 
#define  TYPE_UCHAR 132 
#define  TYPE_UINT 131 
#define  TYPE_ULLONG 130 
#define  TYPE_ULONG 129 
#define  TYPE_USHORT 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* type_bool ; 
 TYPE_1__* type_uchar ; 
 TYPE_1__* type_uint ; 
 TYPE_1__* type_ullong ; 
 TYPE_1__* type_ulong ; 
 TYPE_1__* type_ushort ; 

Type *unsigned_type(Type *type) {
    switch (type->kind) {
    case TYPE_BOOL:
        return type_bool;
    case TYPE_CHAR:
    case TYPE_SCHAR:
    case TYPE_UCHAR:
        return type_uchar;
    case TYPE_SHORT:
    case TYPE_USHORT:
        return type_ushort;
    case TYPE_INT:
    case TYPE_UINT:
        return type_uint;
    case TYPE_LONG:
    case TYPE_ULONG:
        return type_ulong;
    case TYPE_LLONG:
    case TYPE_ULLONG:
        return type_ullong;
    default:
        assert(0);
        return NULL;
    }
}