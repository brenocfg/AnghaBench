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
struct string_list {int dummy; } ;
typedef  int /*<<< orphan*/  rarch_softfilter_t ;

/* Variables and functions */

__attribute__((used)) static bool append_softfilter_plugs(rarch_softfilter_t *filt,
      struct string_list *list)
{
   (void)filt;
   (void)list;

   return false;
}