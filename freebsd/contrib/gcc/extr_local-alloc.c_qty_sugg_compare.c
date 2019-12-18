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
 int QTY_CMP_SUGG (int) ; 

__attribute__((used)) static int
qty_sugg_compare (int q1, int q2)
{
  int tem = QTY_CMP_SUGG (q1) - QTY_CMP_SUGG (q2);

  if (tem != 0)
    return tem;

  return QTY_CMP_PRI (q2) - QTY_CMP_PRI (q1);
}