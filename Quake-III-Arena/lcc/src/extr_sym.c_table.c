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
typedef  TYPE_1__* Table ;
struct TYPE_5__ {int level; int /*<<< orphan*/  all; struct TYPE_5__* previous; } ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 int /*<<< orphan*/  NEW0 (TYPE_1__*,int /*<<< orphan*/ ) ; 

Table table(Table tp, int level) {
	Table new;

	NEW0(new, FUNC);
	new->previous = tp;
	new->level = level;
	if (tp)
		new->all = tp->all;
	return new;
}