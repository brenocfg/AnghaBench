#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* Type ;
struct TYPE_6__ {scalar_t__* proto; } ;
struct TYPE_7__ {TYPE_1__ f; } ;
struct TYPE_8__ {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ isfunc (TYPE_3__*) ; 
 scalar_t__ voidtype ; 

int variadic(Type ty) {
	if (isfunc(ty) && ty->u.f.proto) {
		int i;
		for (i = 0; ty->u.f.proto[i]; i++)
			;
		return i > 1 && ty->u.f.proto[i-1] == voidtype;
	}
	return 0;
}