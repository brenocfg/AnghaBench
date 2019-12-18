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
#define  IMAGE_TYPE_BMP 131 
#define  IMAGE_TYPE_JPEG 130 
#define  IMAGE_TYPE_PNG 129 
#define  IMAGE_TYPE_TGA 128 
 void* rbmp_alloc () ; 
 void* rjpeg_alloc () ; 
 void* rpng_alloc () ; 
 void* rtga_alloc () ; 

void *image_transfer_new(enum image_type_enum type)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         return rpng_alloc();
#else
         break;
#endif
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
         return rjpeg_alloc();
#else
         break;
#endif
      case IMAGE_TYPE_TGA:
#ifdef HAVE_RTGA
         return rtga_alloc();
#else
         break;
#endif
      case IMAGE_TYPE_BMP:
#ifdef HAVE_RBMP
         return rbmp_alloc();
#else
         break;
#endif
      default:
         break;
   }

   return NULL;
}