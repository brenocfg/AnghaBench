#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  L; int /*<<< orphan*/  b; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  LoadBlock (TYPE_1__*,char*,size_t) ; 
 int /*<<< orphan*/  LoadVar (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/ * luaS_newlstr (int /*<<< orphan*/ ,char*,size_t) ; 
 char* luaZ_openspace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static TString* LoadString(LoadState* S)
{
 size_t size;
 LoadVar(S,size);
 if (size==0)
  return NULL;
 else
 {
  char* s=luaZ_openspace(S->L,S->b,size);
  LoadBlock(S,s,size*sizeof(char));
  return luaS_newlstr(S->L,s,size-1);		/* remove trailing '\0' */
 }
}