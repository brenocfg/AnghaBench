#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/ * pixels32; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pixels32; } ;
typedef  TYPE_1__ SuperBlock ;
typedef  TYPE_2__ MacroBlock ;

/* Variables and functions */

__attribute__((used)) static void insert_mb_into_sb(SuperBlock* sb, MacroBlock mb, unsigned index) {
   // Formula: ((index / 4) * 16 + (index % 4) * 2) / 2
   uint32_t *dst = sb->pixels32 + index + (index & -4);

   // This technically violates C99 aliasing rules, but it should be safe.
   dst[0] = mb.pixels32[0];
   dst[4] = mb.pixels32[1];
}