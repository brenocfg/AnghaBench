#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* Type ;
struct TYPE_6__ {int typeno; } ;
struct TYPE_7__ {TYPE_1__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  asgncode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbxout (TYPE_2__*) ; 

__attribute__((used)) static int dbxtype(Type ty) {
	asgncode(ty, 0);
	dbxout(ty);
	return ty->x.typeno;
}