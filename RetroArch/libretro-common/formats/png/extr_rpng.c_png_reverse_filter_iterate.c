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
struct TYPE_6__ {scalar_t__ interlace; } ;
struct TYPE_5__ {scalar_t__ process; TYPE_2__ ihdr; } ;
typedef  TYPE_1__ rpng_t ;

/* Variables and functions */
 int png_reverse_filter_adam7 (int /*<<< orphan*/ **,TYPE_2__*,scalar_t__) ; 
 int png_reverse_filter_regular_iterate (int /*<<< orphan*/ **,TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int png_reverse_filter_iterate(rpng_t *rpng, uint32_t **data)
{
   if (!rpng)
      return false;

   if (rpng->ihdr.interlace && rpng->process)
      return png_reverse_filter_adam7(data, &rpng->ihdr, rpng->process);

   return png_reverse_filter_regular_iterate(data, &rpng->ihdr, rpng->process);
}