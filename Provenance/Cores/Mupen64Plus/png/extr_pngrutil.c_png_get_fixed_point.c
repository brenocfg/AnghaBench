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
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/ * png_structrp ;
typedef  int /*<<< orphan*/  png_fixed_point ;
typedef  int /*<<< orphan*/  png_const_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FIXED_ERROR ; 
 scalar_t__ PNG_UINT_31_MAX ; 
 scalar_t__ png_get_uint_32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_warning (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static png_fixed_point /* PRIVATE */
png_get_fixed_point(png_structrp png_ptr, png_const_bytep buf)
{
   png_uint_32 uval = png_get_uint_32(buf);

   if (uval <= PNG_UINT_31_MAX)
      return (png_fixed_point)uval; /* known to be in range */

   /* The caller can turn off the warning by passing NULL. */
   if (png_ptr != NULL)
      png_warning(png_ptr, "PNG fixed point integer out of range");

   return PNG_FIXED_ERROR;
}