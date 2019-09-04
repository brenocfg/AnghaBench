#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {size_t len; unsigned int hash; scalar_t__ extra; } ;
struct TYPE_7__ {TYPE_1__ tsv; } ;
struct TYPE_8__ {TYPE_2__ ts; } ;
typedef  TYPE_2__ TString ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_4__* luaC_newobj (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,char const*,size_t) ; 

__attribute__((used)) static TString *createstrobj (lua_State *L, const char *str, size_t l,
                              int tag, unsigned int h, GCObject **list) {
  TString *ts;
  size_t totalsize;  /* total size of TString object */
  totalsize = sizeof(TString) + ((l + 1) * sizeof(char));
  ts = &luaC_newobj(L, tag, totalsize, list, 0)->ts;
  ts->tsv.len = l;
  ts->tsv.hash = h;
  ts->tsv.extra = 0;
  memcpy(ts+1, str, l*sizeof(char));
  ((char *)(ts+1))[l] = '\0';  /* ending 0 */
  return ts;
}