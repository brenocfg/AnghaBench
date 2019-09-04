#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_19__ {int currentline; int isvararg; int istailcall; char* namewhat; int /*<<< orphan*/ * name; int /*<<< orphan*/  nparams; int /*<<< orphan*/  nups; } ;
typedef  TYPE_4__ lua_Debug ;
struct TYPE_21__ {int callstatus; struct TYPE_21__* previous; } ;
struct TYPE_18__ {TYPE_2__* p; } ;
struct TYPE_16__ {int /*<<< orphan*/  nupvalues; } ;
struct TYPE_20__ {TYPE_3__ l; TYPE_1__ c; } ;
struct TYPE_17__ {int is_vararg; int /*<<< orphan*/  numparams; } ;
typedef  TYPE_5__ Closure ;
typedef  TYPE_6__ CallInfo ;

/* Variables and functions */
 int CIST_TAIL ; 
 int currentline (TYPE_6__*) ; 
 int /*<<< orphan*/  funcinfo (TYPE_4__*,TYPE_5__*) ; 
 char* getfuncname (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isLua (TYPE_6__*) ; 
 int /*<<< orphan*/  noLuaClosure (TYPE_5__*) ; 

__attribute__((used)) static int auxgetinfo (lua_State *L, const char *what, lua_Debug *ar,
                       Closure *f, CallInfo *ci) {
  int status = 1;
  for (; *what; what++) {
    switch (*what) {
      case 'S': {
        funcinfo(ar, f);
        break;
      }
      case 'l': {
        ar->currentline = (ci && isLua(ci)) ? currentline(ci) : -1;
        break;
      }
      case 'u': {
        ar->nups = (f == NULL) ? 0 : f->c.nupvalues;
        if (noLuaClosure(f)) {
          ar->isvararg = 1;
          ar->nparams = 0;
        }
        else {
          ar->isvararg = f->l.p->is_vararg;
          ar->nparams = f->l.p->numparams;
        }
        break;
      }
      case 't': {
        ar->istailcall = (ci) ? ci->callstatus & CIST_TAIL : 0;
        break;
      }
      case 'n': {
        /* calling function is a known Lua function? */
        if (ci && !(ci->callstatus & CIST_TAIL) && isLua(ci->previous))
          ar->namewhat = getfuncname(L, ci->previous, &ar->name);
        else
          ar->namewhat = NULL;
        if (ar->namewhat == NULL) {
          ar->namewhat = "";  /* not found */
          ar->name = NULL;
        }
        break;
      }
      case 'L':
      case 'f':  /* handled by lua_getinfo */
        break;
      default: status = 0;  /* invalid option */
    }
  }
  return status;
}