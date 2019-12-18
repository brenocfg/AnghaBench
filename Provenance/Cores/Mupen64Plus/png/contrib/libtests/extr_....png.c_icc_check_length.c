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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_const_structrp ;
typedef  int /*<<< orphan*/  png_const_charp ;
typedef  int /*<<< orphan*/  png_colorspacerp ;

/* Variables and functions */
 int png_icc_profile_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static int /* bool */
icc_check_length(png_const_structrp png_ptr, png_colorspacerp colorspace,
    png_const_charp name, png_uint_32 profile_length)
{
   if (profile_length < 132)
      return png_icc_profile_error(png_ptr, colorspace, name, profile_length,
          "too short");

   return 1;
}