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
struct TYPE_3__ {int img_buffer; int img_buffer_end; } ;
typedef  TYPE_1__ rbmp_context ;

/* Variables and functions */

__attribute__((used)) static void rbmp_skip(rbmp_context *s, int n)
{
   if (n < 0)
   {
      s->img_buffer = s->img_buffer_end;
      return;
   }

   s->img_buffer += n;
}