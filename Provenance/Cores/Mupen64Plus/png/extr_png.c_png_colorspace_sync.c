#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_inforp ;
typedef  TYPE_2__* png_const_structrp ;
struct TYPE_8__ {int /*<<< orphan*/  colorspace; } ;
struct TYPE_7__ {int /*<<< orphan*/  colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_colorspace_sync_info (TYPE_2__*,TYPE_1__*) ; 

void /* PRIVATE */
png_colorspace_sync(png_const_structrp png_ptr, png_inforp info_ptr)
{
   if (info_ptr == NULL) /* reduce code size; check here not in the caller */
      return;

   info_ptr->colorspace = png_ptr->colorspace;
   png_colorspace_sync_info(png_ptr, info_ptr);
}