#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * v; } ;
typedef  TYPE_2__ UpVal ;
struct TYPE_14__ {int nupvalues; int /*<<< orphan*/ * upvalue; } ;
struct TYPE_13__ {TYPE_2__** upvals; TYPE_3__* p; } ;
struct TYPE_12__ {int sizeupvalues; TYPE_1__* upvalues; } ;
struct TYPE_10__ {int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  TString ;
typedef  int /*<<< orphan*/  StkId ;
typedef  TYPE_3__ Proto ;
typedef  TYPE_4__ LClosure ;
typedef  TYPE_5__ CClosure ;

/* Variables and functions */
#define  LUA_TCCL 129 
#define  LUA_TLCL 128 
 TYPE_5__* clCvalue (int /*<<< orphan*/ ) ; 
 TYPE_4__* clLvalue (int /*<<< orphan*/ ) ; 
 char const* getstr (int /*<<< orphan*/ *) ; 
 int ttype (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *aux_upvalue (StkId fi, int n, TValue **val,
                                CClosure **owner, UpVal **uv) {
  switch (ttype(fi)) {
    case LUA_TCCL: {  /* C closure */
      CClosure *f = clCvalue(fi);
      if (!(1 <= n && n <= f->nupvalues)) return NULL;
      *val = &f->upvalue[n-1];
      if (owner) *owner = f;
      return "";
    }
    case LUA_TLCL: {  /* Lua closure */
      LClosure *f = clLvalue(fi);
      TString *name;
      Proto *p = f->p;
      if (!(1 <= n && n <= p->sizeupvalues)) return NULL;
      *val = f->upvals[n-1]->v;
      if (uv) *uv = f->upvals[n - 1];
      name = p->upvalues[n-1].name;
      return (name == NULL) ? "(*no name)" : getstr(name);
    }
    default: return NULL;  /* not a closure */
  }
}