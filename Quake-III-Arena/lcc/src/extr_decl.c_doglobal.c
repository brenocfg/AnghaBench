#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ size; TYPE_12__* type; } ;
struct TYPE_16__ {int defined; scalar_t__ sclass; char* name; TYPE_5__* type; int /*<<< orphan*/  generated; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* stabsym ) (TYPE_1__*) ;int /*<<< orphan*/  (* space ) (scalar_t__) ;int /*<<< orphan*/  (* import ) (TYPE_1__*) ;} ;
struct TYPE_14__ {scalar_t__ size; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 scalar_t__ AUTO ; 
 int /*<<< orphan*/  BSS ; 
 scalar_t__ EXTERN ; 
 TYPE_13__* IR ; 
 scalar_t__ Pflag ; 
 scalar_t__ STATIC ; 
 TYPE_5__* array (TYPE_12__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  defglobal (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,TYPE_5__*,char*) ; 
 scalar_t__ glevel ; 
 scalar_t__ isarray (TYPE_5__*) ; 
 scalar_t__ isfunc (TYPE_5__*) ; 
 int /*<<< orphan*/  printdecl (TYPE_1__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (scalar_t__) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*) ; 

__attribute__((used)) static void doglobal(Symbol p, void *cl) {
	if (!p->defined && (p->sclass == EXTERN
	|| isfunc(p->type) && p->sclass == AUTO))
		(*IR->import)(p);
	else if (!p->defined && !isfunc(p->type)
	&& (p->sclass == AUTO || p->sclass == STATIC)) {
		if (isarray(p->type)
		&& p->type->size == 0 && p->type->type->size > 0)
			p->type = array(p->type->type, 1, 0);
		if (p->type->size > 0) {
			defglobal(p, BSS);
			(*IR->space)(p->type->size);
			if (glevel > 0 && IR->stabsym)
				(*IR->stabsym)(p);
		} else
			error("undefined size for `%t %s'\n",
				p->type, p->name);
		p->defined = 1;
	}
	if (Pflag
	&& !isfunc(p->type)
	&& !p->generated && p->sclass != EXTERN)
		printdecl(p, p->type);
}