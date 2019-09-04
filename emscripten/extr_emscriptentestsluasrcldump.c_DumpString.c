#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int len; } ;
struct TYPE_6__ {TYPE_1__ tsv; } ;
typedef  TYPE_2__ TString ;
typedef  int /*<<< orphan*/  DumpState ;

/* Variables and functions */
 int /*<<< orphan*/  DumpBlock (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DumpVar (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getstr (TYPE_2__ const*) ; 

__attribute__((used)) static void DumpString(const TString* s, DumpState* D)
{
 if (s==NULL)
 {
  size_t size=0;
  DumpVar(size,D);
 }
 else
 {
  size_t size=s->tsv.len+1;		/* include trailing '\0' */
  DumpVar(size,D);
  DumpBlock(getstr(s),size*sizeof(char),D);
 }
}