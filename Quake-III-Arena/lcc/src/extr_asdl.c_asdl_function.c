#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  list_ty ;
typedef  int /*<<< orphan*/ * Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  CODE ; 
 int /*<<< orphan*/  Seq_addhi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Seq_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  asdl_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  asdl_segment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dopending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emitcode () ; 
 int /*<<< orphan*/  gencode (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  interfaces ; 
 int /*<<< orphan*/  put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcc_Function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symboluid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_generic_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void asdl_function(Symbol f, Symbol caller[], Symbol callee[], int ncalls) {
	list_ty codelist = Seq_new(0), save, calleelist = Seq_new(0), callerlist = Seq_new(0);
	int i;

	dopending(f);
	for (i = 0; caller[i] != NULL; i++) {
		asdl_local(caller[i]);
		Seq_addhi(callerlist, to_generic_int(symboluid(caller[i])));
	}
	for (i = 0; callee[i] != NULL; i++) {
		asdl_local(callee[i]);
		Seq_addhi(calleelist, to_generic_int(symboluid(callee[i])));
	}
	save = interfaces;
	interfaces = codelist;
	gencode(caller, callee);
	asdl_segment(CODE);
	emitcode();
	interfaces = save;
	put(rcc_Function(symboluid(f), callerlist, calleelist, ncalls, codelist));
}