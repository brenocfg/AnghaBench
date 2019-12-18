#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ count; TYPE_1__** syms; } ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__* Symbol ;
typedef  TYPE_2__* Node ;

/* Variables and functions */
 scalar_t__ ADDRL ; 
 scalar_t__ INDIR ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_2__* newnode (scalar_t__,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ttob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  voidptype ; 

__attribute__((used)) static Node tmpnode(Node p) {
	Symbol tmp = p->syms[2];

	assert(tmp);
	if (--p->count == 0)
		p->syms[2] = NULL;
	p = newnode(INDIR + ttob(tmp->type),
		newnode(ADDRL + ttob(voidptype), NULL, NULL, tmp), NULL, NULL);
	p->count = 1;
	return p;
}