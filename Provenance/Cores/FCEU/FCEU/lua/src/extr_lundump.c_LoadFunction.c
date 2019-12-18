#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {scalar_t__ nCcalls; int /*<<< orphan*/  top; } ;
struct TYPE_22__ {TYPE_3__* L; } ;
struct TYPE_21__ {void* maxstacksize; void* is_vararg; void* numparams; void* nups; void* lastlinedefined; void* linedefined; int /*<<< orphan*/ * source; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ Proto ;
typedef  TYPE_2__ LoadState ;

/* Variables and functions */
 int /*<<< orphan*/  IF (int,char*) ; 
 scalar_t__ LUAI_MAXCCALLS ; 
 void* LoadByte (TYPE_2__*) ; 
 int /*<<< orphan*/  LoadCode (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  LoadConstants (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  LoadDebug (TYPE_2__*,TYPE_1__*) ; 
 void* LoadInt (TYPE_2__*) ; 
 int /*<<< orphan*/ * LoadString (TYPE_2__*) ; 
 int /*<<< orphan*/  error (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  incr_top (TYPE_3__*) ; 
 TYPE_1__* luaF_newproto (TYPE_3__*) ; 
 int /*<<< orphan*/  luaG_checkcode (TYPE_1__*) ; 
 int /*<<< orphan*/  setptvalue2s (TYPE_3__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static Proto* LoadFunction(LoadState* S, TString* p)
{
 Proto* f;
 if (++S->L->nCcalls > LUAI_MAXCCALLS) error(S,"code too deep");
 f=luaF_newproto(S->L);
 setptvalue2s(S->L,S->L->top,f); incr_top(S->L);
 f->source=LoadString(S); if (f->source==NULL) f->source=p;
 f->linedefined=LoadInt(S);
 f->lastlinedefined=LoadInt(S);
 f->nups=LoadByte(S);
 f->numparams=LoadByte(S);
 f->is_vararg=LoadByte(S);
 f->maxstacksize=LoadByte(S);
 LoadCode(S,f);
 LoadConstants(S,f);
 LoadDebug(S,f);
 IF (!luaG_checkcode(f), "bad code");
 S->L->top--;
 S->L->nCcalls--;
 return f;
}