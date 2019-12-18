#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int len; } ;
typedef  TYPE_1__ Type ;

/* Variables and functions */
 TYPE_1__* copy_type (TYPE_1__*) ; 

__attribute__((used)) static Type *copy_incomplete_type(Type *ty) {
    if (!ty) return NULL;
    return (ty->len == -1) ? copy_type(ty) : ty;
}