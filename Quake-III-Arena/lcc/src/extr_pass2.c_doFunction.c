#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  TYPE_5__* rcc_interface_ty ;
struct TYPE_19__ {int /*<<< orphan*/ * next; } ;
struct TYPE_13__ {int /*<<< orphan*/ ** callee; } ;
struct TYPE_14__ {TYPE_1__ f; } ;
struct TYPE_18__ {int defined; TYPE_2__ u; } ;
struct TYPE_15__ {int f; int /*<<< orphan*/  ncalls; int /*<<< orphan*/  codelist; int /*<<< orphan*/  callee; int /*<<< orphan*/  caller; } ;
struct TYPE_16__ {TYPE_3__ rcc_Function; } ;
struct TYPE_17__ {TYPE_4__ v; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* function ) (TYPE_6__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/ * Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  FUNC ; 
 TYPE_11__* IR ; 
 int /*<<< orphan*/  LABELS ; 
 int /*<<< orphan*/  Seq_free (int /*<<< orphan*/ *) ; 
 int Seq_length (int /*<<< orphan*/ ) ; 
 int* Seq_remlo (int /*<<< orphan*/ ) ; 
 TYPE_6__* cfunc ; 
 TYPE_8__ codehead ; 
 TYPE_8__* codelist ; 
 int /*<<< orphan*/  enterscope () ; 
 int /*<<< orphan*/  exitscope () ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  interface (int*) ; 
 int /*<<< orphan*/ * labels ; 
 int /*<<< orphan*/ ** newarray (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* uid2symbol (int) ; 

__attribute__((used)) static void doFunction(rcc_interface_ty in) {
	int i, n;
	Symbol *caller, *callee;

	/*
	 Initialize:
	  define the function symbol,
	  initialize callee and caller arrays.
	*/
	cfunc = uid2symbol(in->v.rcc_Function.f);
	labels = table(NULL, LABELS);
	enterscope();
	n = Seq_length(in->v.rcc_Function.caller);
	caller = newarray(n + 1, sizeof *caller, FUNC);
	for (i = 0; i < n; i++) {
		int *uid = Seq_remlo(in->v.rcc_Function.caller);
		caller[i] = uid2symbol(*uid);
		free(uid);
	}
	caller[i] = NULL;
	Seq_free(&in->v.rcc_Function.caller);
	callee = newarray(n + 1, sizeof *callee, FUNC);
	for (i = 0; i < n; i++) {
		int *uid = Seq_remlo(in->v.rcc_Function.callee);
		callee[i] = uid2symbol(*uid);
		free(uid);
	}
	callee[i] = NULL;
	Seq_free(&in->v.rcc_Function.callee);
	cfunc->u.f.callee = callee;
	cfunc->defined = 1;
	/*
	 Initialize the code list,
	  traverse the interfaces inside the function;
	  each call appends code list entries.
	*/
	codelist = &codehead;
	codelist->next = NULL;
	n = Seq_length(in->v.rcc_Function.codelist);
	for (i = 0; i < n; i++)
		interface(Seq_remlo(in->v.rcc_Function.codelist));
	Seq_free(&in->v.rcc_Function.codelist);
	/*
	 Call the back end,
	 Wrap-up.
	*/
	exitscope();
	(*IR->function)(cfunc, caller, callee, in->v.rcc_Function.ncalls);
	cfunc = NULL;
	labels = NULL;
}