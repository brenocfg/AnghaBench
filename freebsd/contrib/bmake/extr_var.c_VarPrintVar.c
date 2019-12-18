#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ Var ;

/* Variables and functions */
 char* Buf_GetAll (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static void
VarPrintVar(void *vp)
{
    Var    *v = (Var *)vp;
    fprintf(debug_file, "%-16s = %s\n", v->name, Buf_GetAll(&v->val, NULL));
}