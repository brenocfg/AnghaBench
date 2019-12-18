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
typedef  TYPE_1__* Type ;
struct TYPE_7__ {struct TYPE_7__* type; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (char*,char*) ; 
 scalar_t__ isarray (TYPE_1__*) ; 
 TYPE_1__* ptr (TYPE_1__*) ; 

Type atop(Type ty) {
	if (isarray(ty))
		return ptr(ty->type);
	error("type error: %s\n", "array expected");
	return ptr(ty);
}