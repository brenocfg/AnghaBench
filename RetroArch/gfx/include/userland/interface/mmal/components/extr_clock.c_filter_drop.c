#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t first; int /*<<< orphan*/  count; int /*<<< orphan*/  length; scalar_t__* h; int /*<<< orphan*/  sum; } ;
typedef  TYPE_1__ FILTER_T ;

/* Variables and functions */
 size_t filter_index_wrap (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filter_drop(FILTER_T *filter)
{
   if (!filter->count)
      return;

   filter->sum -= filter->h[filter->first];
   filter->first = filter_index_wrap(filter->first, filter->length);
   filter->count--;
}