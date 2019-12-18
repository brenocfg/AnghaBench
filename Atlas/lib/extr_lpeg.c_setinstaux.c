#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int offset; int aux; int /*<<< orphan*/  code; } ;
struct TYPE_5__ {TYPE_1__ i; } ;
typedef  int /*<<< orphan*/  Opcode ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */

__attribute__((used)) static void setinstaux (Instruction *i, Opcode op, int offset, int aux) {
  i->i.code = op;
  i->i.offset = offset;
  i->i.aux = aux;
}