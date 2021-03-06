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
typedef  int /*<<< orphan*/  rpng_t ;
typedef  enum image_type_enum { ____Placeholder_image_type_enum } image_type_enum ;

/* Variables and functions */
#define  IMAGE_TYPE_BMP 132 
#define  IMAGE_TYPE_JPEG 131 
#define  IMAGE_TYPE_NONE 130 
#define  IMAGE_TYPE_PNG 129 
#define  IMAGE_TYPE_TGA 128 
 int /*<<< orphan*/  rpng_start (int /*<<< orphan*/ *) ; 

bool image_transfer_start(void *data, enum image_type_enum type)
{

   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         if (!rpng_start((rpng_t*)data))
            break;
         return true;
#else
         break;
#endif
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
         return true;
#else
         break;
#endif
      case IMAGE_TYPE_TGA:
#ifdef HAVE_RTGA
         return true;
#else
         break;
#endif
      case IMAGE_TYPE_BMP:
         return true;
      case IMAGE_TYPE_NONE:
         break;
   }

   return false;
}