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
struct z_candidate {int viable; struct z_candidate* next; } ;

/* Variables and functions */

__attribute__((used)) static bool
any_strictly_viable (struct z_candidate *cands)
{
  for (; cands; cands = cands->next)
    if (cands->viable == 1)
      return true;
  return false;
}