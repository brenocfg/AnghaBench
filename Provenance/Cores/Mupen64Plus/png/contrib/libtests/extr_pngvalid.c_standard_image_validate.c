#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ h; TYPE_2__* ps; } ;
typedef  TYPE_1__ standard_display ;
typedef  scalar_t__ png_uint_32 ;
typedef  int /*<<< orphan*/  png_const_structp ;
struct TYPE_6__ {int validated; } ;

/* Variables and functions */
 int /*<<< orphan*/  standard_row_validate (TYPE_1__*,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  store_image_check (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
standard_image_validate(standard_display *dp, png_const_structp pp, int iImage,
    int iDisplay)
{
   png_uint_32 y;

   if (iImage >= 0)
      store_image_check(dp->ps, pp, iImage);

   if (iDisplay >= 0)
      store_image_check(dp->ps, pp, iDisplay);

   for (y=0; y<dp->h; ++y)
      standard_row_validate(dp, pp, iImage, iDisplay, y);

   /* This avoids false positives if the validation code is never called! */
   dp->ps->validated = 1;
}