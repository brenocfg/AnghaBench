#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  maxstacksize; int /*<<< orphan*/  is_vararg; int /*<<< orphan*/  numparams; int /*<<< orphan*/  lastlinedefined; int /*<<< orphan*/  linedefined; } ;
typedef  TYPE_1__ Proto ;
typedef  int /*<<< orphan*/  DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpChar (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpCode (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpConstants (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpDebug (TYPE_1__ const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpInt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpUpvalues (TYPE_1__ const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DumpFunction(const Proto* f, DumpState* D)
{
 DumpInt(f->linedefined,D);
 DumpInt(f->lastlinedefined,D);
 DumpChar(f->numparams,D);
 DumpChar(f->is_vararg,D);
 DumpChar(f->maxstacksize,D);
 DumpCode(f,D);
 DumpConstants(f,D);
 DumpUpvalues(f,D);
 DumpDebug(f,D);
}