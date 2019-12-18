#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int QTY_CMP_PRI (int) ; 

__attribute__((used)) static int
qty_compare_1 (const void *q1p, const void *q2p)
{
  int q1 = *(const int *) q1p, q2 = *(const int *) q2p;
  int tem = QTY_CMP_PRI (q2) - QTY_CMP_PRI (q1);

  if (tem != 0)
    return tem;

  /* If qtys are equally good, sort by qty number,
     so that the results of qsort leave nothing to chance.  */
  return q1 - q2;
}