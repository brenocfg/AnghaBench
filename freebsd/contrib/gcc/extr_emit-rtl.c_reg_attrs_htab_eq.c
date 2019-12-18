#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ decl; scalar_t__ offset; } ;
typedef  TYPE_1__ reg_attrs ;

/* Variables and functions */

__attribute__((used)) static int
reg_attrs_htab_eq (const void *x, const void *y)
{
  reg_attrs *p = (reg_attrs *) x;
  reg_attrs *q = (reg_attrs *) y;

  return (p->decl == q->decl && p->offset == q->offset);
}