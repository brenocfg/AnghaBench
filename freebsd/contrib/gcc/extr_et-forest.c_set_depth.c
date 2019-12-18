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
struct et_occ {int depth; int /*<<< orphan*/  min; } ;

/* Variables and functions */

__attribute__((used)) static inline void
set_depth (struct et_occ *occ, int d)
{
  if (!occ)
    return;

  occ->min += d - occ->depth;
  occ->depth = d;
}