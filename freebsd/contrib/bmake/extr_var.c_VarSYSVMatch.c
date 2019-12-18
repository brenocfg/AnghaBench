#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ varSpace; } ;
typedef  TYPE_1__ Var_Parse_State ;
struct TYPE_5__ {int /*<<< orphan*/  rhs; int /*<<< orphan*/  lhs; } ;
typedef  TYPE_2__ VarPattern ;
typedef  int /*<<< orphan*/  GNode ;
typedef  int /*<<< orphan*/  Buffer ;
typedef  scalar_t__ Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  Buf_AddByte (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Buf_AddBytes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 char* Str_SYSVMatch (char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Str_SYSVSubst (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VARF_WANTRES ; 
 char* Var_Subst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static Boolean
VarSYSVMatch(GNode *ctx, Var_Parse_State *vpstate,
	     char *word, Boolean addSpace, Buffer *buf,
	     void *patp)
{
    int len;
    char *ptr;
    VarPattern 	  *pat = (VarPattern *)patp;
    char *varexp;

    if (addSpace && vpstate->varSpace)
	Buf_AddByte(buf, vpstate->varSpace);

    addSpace = TRUE;

    if ((ptr = Str_SYSVMatch(word, pat->lhs, &len)) != NULL) {
        varexp = Var_Subst(NULL, pat->rhs, ctx, VARF_WANTRES);
	Str_SYSVSubst(buf, varexp, ptr, len);
	free(varexp);
    } else {
	Buf_AddBytes(buf, strlen(word), word);
    }

    return(addSpace);
}