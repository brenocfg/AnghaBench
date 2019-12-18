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
struct TYPE_3__ {void* height; void* width; void* y; void* x; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_RECT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int sscanf (char const*,char*,void**,void**,...) ; 

MMAL_STATUS_T mmal_parse_geometry(MMAL_RECT_T *dest, const char *str)
{
   MMAL_STATUS_T ret;
   uint32_t w, h, x, y;
   x = y = w = h = 0;
   /* coverity[secure_coding] */
   if (sscanf(str, "%d*%d+%d+%d", &w,&h,&x,&y) == 4 ||
       sscanf(str, "%d*%d", &w,&h) == 2)
   {
      dest->x = x;
      dest->y = y;
      dest->width = w;
      dest->height = h;
      ret = MMAL_SUCCESS;
   }
   else
   {
      ret = MMAL_EINVAL;
   }
   return ret;
}