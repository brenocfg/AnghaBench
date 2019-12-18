#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ code; } ;
struct TYPE_8__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 scalar_t__ IEnd ; 
 int /*<<< orphan*/  printinst (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sizei (TYPE_2__*) ; 

__attribute__((used)) static void printpatt (Instruction *p) {
  Instruction *op = p;
  for (;;) {
    printinst(op, p);
    if (p->i.code == IEnd) break;
    p += sizei(p);
  }
}