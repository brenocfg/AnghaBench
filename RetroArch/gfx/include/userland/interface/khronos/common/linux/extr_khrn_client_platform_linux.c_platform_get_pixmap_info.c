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
typedef  void* uint32_t ;
struct TYPE_3__ {scalar_t__ format; scalar_t__ storage; scalar_t__ aux; scalar_t__ stride; void* height; void* width; } ;
typedef  TYPE_1__ KHRN_IMAGE_WRAP_T ;
typedef  scalar_t__ EGLNativePixmapType ;

/* Variables and functions */
 scalar_t__ convert_format (void*) ; 

bool platform_get_pixmap_info(EGLNativePixmapType pixmap, KHRN_IMAGE_WRAP_T *image)
{
   image->format = convert_format(((uint32_t *)pixmap)[4]);
   image->width = ((uint32_t *)pixmap)[2];
   image->height = ((uint32_t *)pixmap)[3];

   /* can't actually access data */
   image->stride = 0;
   image->aux = 0;
   image->storage = 0;

   return image->format != 0;
}