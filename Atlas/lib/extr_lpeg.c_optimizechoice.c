#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ code; int offset; int /*<<< orphan*/  aux; } ;
struct TYPE_10__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 scalar_t__ IChoice ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check2test (TYPE_2__*,int) ; 
 scalar_t__ ischeck (TYPE_2__*) ; 
 int /*<<< orphan*/  op_step (TYPE_2__*) ; 
 int /*<<< orphan*/  rotate (TYPE_2__*,int,int) ; 
 int sizei (TYPE_2__*) ; 

__attribute__((used)) static void optimizechoice (Instruction *p) {
  assert(p->i.code == IChoice);
  if (ischeck(p + 1)) {
    int lc = sizei(p + 1);
    rotate(p, lc, 1);
    assert(ischeck(p) && (p + lc)->i.code == IChoice);
    (p + lc)->i.aux = op_step(p);
    check2test(p, (p + lc)->i.offset);
    (p + lc)->i.offset -= lc;
  }
}