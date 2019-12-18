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
typedef  int /*<<< orphan*/  ushort_t ;
struct TYPE_5__ {char* dd_name; int /*<<< orphan*/ * dd_next; int /*<<< orphan*/ * dd_node; int /*<<< orphan*/  dd_type; int /*<<< orphan*/ * dd_ctfp; scalar_t__ dd_attr; int /*<<< orphan*/  dd_kind; } ;
typedef  TYPE_1__ dt_decl_t ;
struct TYPE_6__ {int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* malloc (int) ; 
 TYPE_2__* yypcb ; 

dt_decl_t *
dt_decl_alloc(ushort_t kind, char *name)
{
	dt_decl_t *ddp = malloc(sizeof (dt_decl_t));

	if (ddp == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	ddp->dd_kind = kind;
	ddp->dd_attr = 0;
	ddp->dd_ctfp = NULL;
	ddp->dd_type = CTF_ERR;
	ddp->dd_name = name;
	ddp->dd_node = NULL;
	ddp->dd_next = NULL;

	return (ddp);
}