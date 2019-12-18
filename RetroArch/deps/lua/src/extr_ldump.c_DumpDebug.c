#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ strip; } ;
struct TYPE_12__ {int sizelineinfo; int sizelocvars; int sizeupvalues; TYPE_2__* upvalues; TYPE_1__* locvars; int /*<<< orphan*/  lineinfo; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int startpc; int endpc; int /*<<< orphan*/  varname; } ;
typedef  TYPE_3__ Proto ;
typedef  TYPE_4__ DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpInt (int,TYPE_4__*) ; 
 int /*<<< orphan*/  DumpString (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  DumpVector (int /*<<< orphan*/ ,int,TYPE_4__*) ; 

__attribute__((used)) static void DumpDebug (const Proto *f, DumpState *D) {
  int i, n;
  n = (D->strip) ? 0 : f->sizelineinfo;
  DumpInt(n, D);
  DumpVector(f->lineinfo, n, D);
  n = (D->strip) ? 0 : f->sizelocvars;
  DumpInt(n, D);
  for (i = 0; i < n; i++) {
    DumpString(f->locvars[i].varname, D);
    DumpInt(f->locvars[i].startpc, D);
    DumpInt(f->locvars[i].endpc, D);
  }
  n = (D->strip) ? 0 : f->sizeupvalues;
  DumpInt(n, D);
  for (i = 0; i < n; i++)
    DumpString(f->upvalues[i].name, D);
}