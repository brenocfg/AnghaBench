#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  context; } ;
typedef  int /*<<< orphan*/  Hash_Search ;
typedef  int /*<<< orphan*/  Hash_Entry ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/ * Hash_EnumFirst (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Hash_EnumNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Hash_GetValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VarPrintVar (int /*<<< orphan*/ ) ; 

void
Var_Dump(GNode *ctxt)
{
    Hash_Search search;
    Hash_Entry *h;

    for (h = Hash_EnumFirst(&ctxt->context, &search);
	 h != NULL;
	 h = Hash_EnumNext(&search)) {
	    VarPrintVar(Hash_GetValue(h));
    }
}