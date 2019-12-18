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
struct TYPE_2__ {int optional; int nregs; scalar_t__ class; } ;

/* Variables and functions */
 int* reg_class_size ; 
 TYPE_1__* rld ; 

__attribute__((used)) static int
reload_reg_class_lower (const void *r1p, const void *r2p)
{
  int r1 = *(const short *) r1p, r2 = *(const short *) r2p;
  int t;

  /* Consider required reloads before optional ones.  */
  t = rld[r1].optional - rld[r2].optional;
  if (t != 0)
    return t;

  /* Count all solitary classes before non-solitary ones.  */
  t = ((reg_class_size[(int) rld[r2].class] == 1)
       - (reg_class_size[(int) rld[r1].class] == 1));
  if (t != 0)
    return t;

  /* Aside from solitaires, consider all multi-reg groups first.  */
  t = rld[r2].nregs - rld[r1].nregs;
  if (t != 0)
    return t;

  /* Consider reloads in order of increasing reg-class number.  */
  t = (int) rld[r1].class - (int) rld[r2].class;
  if (t != 0)
    return t;

  /* If reloads are equally urgent, sort by reload number,
     so that the results of qsort leave nothing to chance.  */
  return r1 - r2;
}