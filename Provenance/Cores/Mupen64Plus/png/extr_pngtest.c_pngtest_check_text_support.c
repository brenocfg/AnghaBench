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
typedef  TYPE_1__* png_textp ;
typedef  int /*<<< orphan*/  png_structp ;
struct TYPE_3__ {int compression; } ;

/* Variables and functions */
#define  PNG_ITXT_COMPRESSION_NONE 131 
#define  PNG_ITXT_COMPRESSION_zTXt 130 
#define  PNG_TEXT_COMPRESSION_NONE 129 
#define  PNG_TEXT_COMPRESSION_zTXt 128 
 int /*<<< orphan*/  png_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unsupported_chunks ; 

__attribute__((used)) static void
pngtest_check_text_support(png_structp png_ptr, png_textp text_ptr,
    int num_text)
{
   while (num_text > 0)
   {
      switch (text_ptr[--num_text].compression)
      {
         case PNG_TEXT_COMPRESSION_NONE:
            break;

         case PNG_TEXT_COMPRESSION_zTXt:
#           ifndef PNG_WRITE_zTXt_SUPPORTED
               ++unsupported_chunks;
               /* In libpng 1.7 this now does an app-error, so stop it: */
               text_ptr[num_text].compression = PNG_TEXT_COMPRESSION_NONE;
#           endif
            break;

         case PNG_ITXT_COMPRESSION_NONE:
         case PNG_ITXT_COMPRESSION_zTXt:
#           ifndef PNG_WRITE_iTXt_SUPPORTED
               ++unsupported_chunks;
               text_ptr[num_text].compression = PNG_TEXT_COMPRESSION_NONE;
#           endif
            break;

         default:
            /* This is an error */
            png_error(png_ptr, "invalid text chunk compression field");
            break;
      }
   }
}