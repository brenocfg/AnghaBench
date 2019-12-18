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
typedef  enum image_type_enum { ____Placeholder_image_type_enum } image_type_enum ;

/* Variables and functions */
 int IMAGE_TYPE_BMP ; 
 int IMAGE_TYPE_JPEG ; 
 int IMAGE_TYPE_NONE ; 
 int IMAGE_TYPE_PNG ; 
 int IMAGE_TYPE_TGA ; 
 scalar_t__ strstr (char const*,char*) ; 

enum image_type_enum image_texture_get_type(const char *path)
{
#ifdef HAVE_RTGA
   if (strstr(path, ".tga"))
      return IMAGE_TYPE_TGA;
#endif
#ifdef HAVE_RPNG
   if (strstr(path, ".png"))
      return IMAGE_TYPE_PNG;
#endif
#ifdef HAVE_RJPEG
   if (strstr(path, ".jpg") || strstr(path, ".jpeg"))
      return IMAGE_TYPE_JPEG;
#endif
#ifdef HAVE_RBMP
   if (strstr(path, ".bmp"))
      return IMAGE_TYPE_BMP;
#endif
   return IMAGE_TYPE_NONE;
}