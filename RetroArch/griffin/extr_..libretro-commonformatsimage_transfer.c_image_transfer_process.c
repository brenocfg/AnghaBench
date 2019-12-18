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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  rtga_t ;
typedef  int /*<<< orphan*/  rpng_t ;
typedef  int /*<<< orphan*/  rjpeg_t ;
typedef  int /*<<< orphan*/  rbmp_t ;
typedef  enum image_type_enum { ____Placeholder_image_type_enum } image_type_enum ;

/* Variables and functions */
#define  IMAGE_TYPE_BMP 132 
#define  IMAGE_TYPE_JPEG 131 
#define  IMAGE_TYPE_NONE 130 
#define  IMAGE_TYPE_PNG 129 
#define  IMAGE_TYPE_TGA 128 
 int rbmp_process_image (int /*<<< orphan*/ *,void**,size_t,unsigned int*,unsigned int*) ; 
 int rjpeg_process_image (int /*<<< orphan*/ *,void**,size_t,unsigned int*,unsigned int*) ; 
 int rpng_process_image (int /*<<< orphan*/ *,void**,size_t,unsigned int*,unsigned int*) ; 
 int rtga_process_image (int /*<<< orphan*/ *,void**,size_t,unsigned int*,unsigned int*) ; 

int image_transfer_process(
      void *data,
      enum image_type_enum type,
      uint32_t **buf, size_t len,
      unsigned *width, unsigned *height)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         return rpng_process_image(
               (rpng_t*)data,
               (void**)buf, len, width, height);
#else
         break;
#endif
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
         return rjpeg_process_image((rjpeg_t*)data,
               (void**)buf, len, width, height);
#else
         break;
#endif
      case IMAGE_TYPE_TGA:
#ifdef HAVE_RTGA
         return rtga_process_image((rtga_t*)data,
               (void**)buf, len, width, height);
#else
         break;
#endif
      case IMAGE_TYPE_BMP:
#ifdef HAVE_RBMP
         return rbmp_process_image((rbmp_t*)data,
               (void**)buf, len, width, height);
#else
         break;
#endif
      case IMAGE_TYPE_NONE:
         break;
   }

   return 0;
}