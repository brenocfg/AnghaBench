#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_4__ {int sclass; int temporary; int generated; int /*<<< orphan*/  type; scalar_t__ scope; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 scalar_t__ LOCAL ; 
 int /*<<< orphan*/  NEW0 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ level ; 
 int /*<<< orphan*/  stringd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempid ; 

Symbol temporary(int scls, Type ty) {
	Symbol p;

	NEW0(p, FUNC);
	p->name = stringd(++tempid);
	p->scope = level < LOCAL ? LOCAL : level;
	p->sclass = scls;
	p->type = ty;
	p->temporary = 1;
	p->generated = 1;
	return p;
}