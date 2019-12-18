#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  val; struct TYPE_4__* name; } ;
typedef  TYPE_1__ Var ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int VAR_FROM_ENV ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static Boolean
VarFreeEnv(Var *v, Boolean destroy)
{
    if ((v->flags & VAR_FROM_ENV) == 0)
	return FALSE;
    free(v->name);
    Buf_Destroy(&v->val, destroy);
    free(v);
    return TRUE;
}