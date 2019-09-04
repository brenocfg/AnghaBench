#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  int lu_mem ;
struct TYPE_21__ {int /*<<< orphan*/  GCmemtrav; int /*<<< orphan*/ * gray; } ;
typedef  TYPE_2__ global_State ;
struct TYPE_20__ {int /*<<< orphan*/  value; } ;
struct TYPE_22__ {TYPE_1__ u; int /*<<< orphan*/ * v; } ;
typedef  TYPE_3__ UpVal ;
typedef  int /*<<< orphan*/  Table ;
struct TYPE_23__ {int /*<<< orphan*/ * env; int /*<<< orphan*/ * metatable; } ;
struct TYPE_19__ {int tt; } ;
struct TYPE_18__ {int /*<<< orphan*/ * gclist; } ;
struct TYPE_17__ {int /*<<< orphan*/ * gclist; } ;
struct TYPE_16__ {int /*<<< orphan*/ * gclist; } ;
struct TYPE_15__ {int /*<<< orphan*/ * gclist; } ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
#define  LUA_TCCL 136 
#define  LUA_TLCL 135 
#define  LUA_TLNGSTR 134 
#define  LUA_TPROTO 133 
#define  LUA_TSHRSTR 132 
#define  LUA_TTABLE 131 
#define  LUA_TTHREAD 130 
#define  LUA_TUPVAL 129 
#define  LUA_TUSERDATA 128 
 TYPE_14__* gch (int /*<<< orphan*/ *) ; 
 TYPE_13__* gco2ccl (int /*<<< orphan*/ *) ; 
 TYPE_12__* gco2lcl (int /*<<< orphan*/ *) ; 
 TYPE_11__* gco2p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2t (int /*<<< orphan*/ *) ; 
 TYPE_10__* gco2th (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gco2ts (int /*<<< orphan*/ *) ; 
 TYPE_4__* gco2u (int /*<<< orphan*/ *) ; 
 TYPE_3__* gco2uv (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gray2black (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linktable (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lua_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  markobject (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  markvalue (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int sizestring (int /*<<< orphan*/ ) ; 
 int sizeudata (TYPE_4__*) ; 
 int /*<<< orphan*/  white2gray (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reallymarkobject (global_State *g, GCObject *o) {
  lu_mem size;
  white2gray(o);
  switch (gch(o)->tt) {
    case LUA_TSHRSTR:
    case LUA_TLNGSTR: {
      size = sizestring(gco2ts(o));
      break;  /* nothing else to mark; make it black */
    }
    case LUA_TUSERDATA: {
      Table *mt = gco2u(o)->metatable;
      markobject(g, mt);
      markobject(g, gco2u(o)->env);
      size = sizeudata(gco2u(o));
      break;
    }
    case LUA_TUPVAL: {
      UpVal *uv = gco2uv(o);
      markvalue(g, uv->v);
      if (uv->v != &uv->u.value)  /* open? */
        return;  /* open upvalues remain gray */
      size = sizeof(UpVal);
      break;
    }
    case LUA_TLCL: {
      gco2lcl(o)->gclist = g->gray;
      g->gray = o;
      return;
    }
    case LUA_TCCL: {
      gco2ccl(o)->gclist = g->gray;
      g->gray = o;
      return;
    }
    case LUA_TTABLE: {
      linktable(gco2t(o), &g->gray);
      return;
    }
    case LUA_TTHREAD: {
      gco2th(o)->gclist = g->gray;
      g->gray = o;
      return;
    }
    case LUA_TPROTO: {
      gco2p(o)->gclist = g->gray;
      g->gray = o;
      return;
    }
    default: lua_assert(0); return;
  }
  gray2black(o);
  g->GCmemtrav += size;
}