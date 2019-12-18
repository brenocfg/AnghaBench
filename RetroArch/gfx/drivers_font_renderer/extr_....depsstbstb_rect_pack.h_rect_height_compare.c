#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ h; scalar_t__ w; } ;
typedef  TYPE_1__ stbrp_rect ;

/* Variables and functions */

__attribute__((used)) static int rect_height_compare(const void *a, const void *b)
{
   stbrp_rect *p = (stbrp_rect *) a;
   stbrp_rect *q = (stbrp_rect *) b;
   if (p->h > q->h)
      return -1;
   if (p->h < q->h)
      return  1;
   return (p->w > q->w) ? -1 : (p->w < q->w);
}