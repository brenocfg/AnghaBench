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
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_5__ {int /*<<< orphan*/ * di_next; int /*<<< orphan*/ * di_extern; int /*<<< orphan*/  di_instr; int /*<<< orphan*/  di_label; } ;
typedef  TYPE_1__ dt_irnode_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_6__ {int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 TYPE_2__* yypcb ; 

__attribute__((used)) static dt_irnode_t *
dt_cg_node_alloc(uint_t label, dif_instr_t instr)
{
	dt_irnode_t *dip = malloc(sizeof (dt_irnode_t));

	if (dip == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	dip->di_label = label;
	dip->di_instr = instr;
	dip->di_extern = NULL;
	dip->di_next = NULL;

	return (dip);
}