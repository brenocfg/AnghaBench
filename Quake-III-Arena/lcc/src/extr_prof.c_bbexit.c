#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Tree ;
struct TYPE_6__ {scalar_t__ defined; } ;
typedef  TYPE_1__* Symbol ;

/* Variables and functions */
 int /*<<< orphan*/  EXTERN ; 
 int /*<<< orphan*/  afunc ; 
 int /*<<< orphan*/  ftype (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inttype ; 
 TYPE_1__* mksymbol (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcall (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  voidptype ; 
 int /*<<< orphan*/  voidtype ; 
 int /*<<< orphan*/  walk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bbexit(Symbol yylink, Symbol f, Tree e) {
	static Symbol epilogue;
	
	if (epilogue == 0) {
		epilogue = mksymbol(EXTERN, "_epilogue", ftype(inttype, voidptype));
		epilogue->defined = 0;
	}
	walk(vcall(epilogue, voidtype, pointer(idtree(afunc)), NULL), 0, 0);
}