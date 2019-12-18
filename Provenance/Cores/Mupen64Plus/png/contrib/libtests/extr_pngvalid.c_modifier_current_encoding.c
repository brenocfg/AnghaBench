#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  current_gamma; TYPE_2__* current_encoding; } ;
typedef  TYPE_1__ png_modifier ;
struct TYPE_7__ {int /*<<< orphan*/  gamma; } ;
typedef  TYPE_2__ color_encoding ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
modifier_current_encoding(const png_modifier *pm, color_encoding *ce)
{
   if (pm->current_encoding != 0)
      *ce = *pm->current_encoding;

   else
      memset(ce, 0, sizeof *ce);

   ce->gamma = pm->current_gamma;
}