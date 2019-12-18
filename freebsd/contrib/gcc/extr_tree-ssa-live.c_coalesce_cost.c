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
 scalar_t__ optimize_size ; 

int
coalesce_cost (int frequency, bool hot, bool critical)
{
  /* Base costs on BB frequencies bounded by 1.  */
  int cost = frequency;

  if (!cost)
    cost = 1;
  if (optimize_size || hot)
    cost = 1;
  /* Inserting copy on critical edge costs more
     than inserting it elsewhere.  */
  if (critical)
    cost *= 2;
  return cost;
}