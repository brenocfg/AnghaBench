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
typedef  int /*<<< orphan*/  uint8_t ;
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
 int /*<<< orphan*/  rbmp_set_buf_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rjpeg_set_buf_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpng_set_buf_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rtga_set_buf_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void image_transfer_set_buffer_ptr(
      void *data,
      enum image_type_enum type,
      void *ptr,
      size_t len)
{
   switch (type)
   {
      case IMAGE_TYPE_PNG:
#ifdef HAVE_RPNG
         rpng_set_buf_ptr((rpng_t*)data, (uint8_t*)ptr, len);
#endif
         break;
      case IMAGE_TYPE_JPEG:
#ifdef HAVE_RJPEG
         rjpeg_set_buf_ptr((rjpeg_t*)data, (uint8_t*)ptr);
#endif
         break;
      case IMAGE_TYPE_TGA:
#ifdef HAVE_RTGA
         rtga_set_buf_ptr((rtga_t*)data, (uint8_t*)ptr);
#endif
         break;
      case IMAGE_TYPE_BMP:
#ifdef HAVE_RBMP
         rbmp_set_buf_ptr((rbmp_t*)data, (uint8_t*)ptr);
#endif
         break;
      case IMAGE_TYPE_NONE:
         break;
   }
}