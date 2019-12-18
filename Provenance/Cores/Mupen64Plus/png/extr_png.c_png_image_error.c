#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_imagep ;
typedef  int /*<<< orphan*/  png_const_charp ;
struct TYPE_4__ {int /*<<< orphan*/  warning_or_error; int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_IMAGE_ERROR ; 
 int /*<<< orphan*/  png_image_free (TYPE_1__*) ; 
 int /*<<< orphan*/  png_safecat (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int /* PRIVATE */
png_image_error(png_imagep image, png_const_charp error_message)
{
   /* Utility to log an error. */
   png_safecat(image->message, (sizeof image->message), 0, error_message);
   image->warning_or_error |= PNG_IMAGE_ERROR;
   png_image_free(image);
   return 0;
}