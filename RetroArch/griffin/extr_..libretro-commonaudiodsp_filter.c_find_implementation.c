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
struct dspfilter_implementation {int /*<<< orphan*/  short_ident; } ;
struct TYPE_5__ {unsigned int num_plugs; TYPE_1__* plugs; } ;
typedef  TYPE_2__ retro_dsp_filter_t ;
struct TYPE_4__ {struct dspfilter_implementation const* impl; } ;

/* Variables and functions */
 scalar_t__ string_is_equal (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static const struct dspfilter_implementation *find_implementation(
      retro_dsp_filter_t *dsp, const char *ident)
{
   unsigned i;
   for (i = 0; i < dsp->num_plugs; i++)
   {
      if (string_is_equal(dsp->plugs[i].impl->short_ident, ident))
         return dsp->plugs[i].impl;
   }

   return NULL;
}