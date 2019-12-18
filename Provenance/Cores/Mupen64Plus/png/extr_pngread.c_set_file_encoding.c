#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  file_encoding; int /*<<< orphan*/  gamma_to_linear; TYPE_4__* image; } ;
typedef  TYPE_5__ png_image_read_control ;
typedef  int /*<<< orphan*/  png_fixed_point ;
struct TYPE_10__ {TYPE_3__* opaque; } ;
struct TYPE_9__ {TYPE_2__* png_ptr; } ;
struct TYPE_7__ {int /*<<< orphan*/  gamma; } ;
struct TYPE_8__ {TYPE_1__ colorspace; } ;

/* Variables and functions */
 int /*<<< orphan*/  P_FILE ; 
 int /*<<< orphan*/  P_LINEAR8 ; 
 int /*<<< orphan*/  P_sRGB ; 
 scalar_t__ png_gamma_not_sRGB (int /*<<< orphan*/ ) ; 
 scalar_t__ png_gamma_significant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_reciprocal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_file_encoding(png_image_read_control *display)
{
   png_fixed_point g = display->image->opaque->png_ptr->colorspace.gamma;
   if (png_gamma_significant(g) != 0)
   {
      if (png_gamma_not_sRGB(g) != 0)
      {
         display->file_encoding = P_FILE;
         display->gamma_to_linear = png_reciprocal(g);
      }

      else
         display->file_encoding = P_sRGB;
   }

   else
      display->file_encoding = P_LINEAR8;
}