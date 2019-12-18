#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
struct TYPE_8__ {int file_encoding; TYPE_1__* image; int /*<<< orphan*/  gamma_to_linear; } ;
typedef  TYPE_3__ png_image_read_control ;
struct TYPE_7__ {int /*<<< orphan*/  png_ptr; } ;
struct TYPE_6__ {TYPE_2__* opaque; } ;

/* Variables and functions */
#define  P_FILE 131 
#define  P_LINEAR 130 
#define  P_LINEAR8 129 
 int P_NOTSET ; 
#define  P_sRGB 128 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 int png_gamma_16bit_correct (int,int /*<<< orphan*/ ) ; 
 int* png_sRGB_table ; 
 int /*<<< orphan*/  set_file_encoding (TYPE_3__*) ; 

__attribute__((used)) static unsigned int
decode_gamma(png_image_read_control *display, png_uint_32 value, int encoding)
{
   if (encoding == P_FILE) /* double check */
      encoding = display->file_encoding;

   if (encoding == P_NOTSET) /* must be the file encoding */
   {
      set_file_encoding(display);
      encoding = display->file_encoding;
   }

   switch (encoding)
   {
      case P_FILE:
         value = png_gamma_16bit_correct(value*257, display->gamma_to_linear);
         break;

      case P_sRGB:
         value = png_sRGB_table[value];
         break;

      case P_LINEAR:
         break;

      case P_LINEAR8:
         value *= 257;
         break;

#ifdef __GNUC__
      default:
         png_error(display->image->opaque->png_ptr,
             "unexpected encoding (internal error)");
#endif
   }

   return value;
}