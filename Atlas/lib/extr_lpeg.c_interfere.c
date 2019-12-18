#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tag; int /*<<< orphan*/  cs; } ;
struct TYPE_7__ {int code; int /*<<< orphan*/  aux; } ;
struct TYPE_8__ {TYPE_1__ i; int /*<<< orphan*/  buff; } ;
typedef  TYPE_2__ Instruction ;
typedef  TYPE_3__ CharsetTag ;

/* Variables and functions */
 int ITestAny ; 
#define  ITestChar 129 
#define  ITestSet 128 
 scalar_t__ NOINFO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exclusiveset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nofail (TYPE_2__*,int) ; 
 int testchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int interfere (Instruction *p1, int l1, CharsetTag *st2) {
  if (nofail(p1, l1))  /* p1 cannot fail? */
    return 0;  /* nothing can intefere with it */
  if (st2->tag == NOINFO) return 1;
  switch (p1->i.code) {
    case ITestChar: return testchar(st2->cs, p1->i.aux);
    case ITestSet: return !exclusiveset(st2->cs, (p1 + 1)->buff);
    default: assert(p1->i.code == ITestAny); return 1;
  }
}