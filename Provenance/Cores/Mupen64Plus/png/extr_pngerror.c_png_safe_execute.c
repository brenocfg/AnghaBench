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
typedef  int /*<<< orphan*/  png_voidp ;
typedef  TYPE_2__* png_imagep ;
typedef  int /*<<< orphan*/  jmp_buf ;
struct TYPE_6__ {TYPE_1__* opaque; } ;
struct TYPE_5__ {int /*<<< orphan*/  error_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  png_image_free (TYPE_2__* volatile) ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 

int /* PRIVATE */
png_safe_execute(png_imagep image_in, int (*function)(png_voidp), png_voidp arg)
{
   volatile png_imagep image = image_in;
   volatile int result;
   volatile png_voidp saved_error_buf;
   jmp_buf safe_jmpbuf;

   /* Safely execute function(arg) with png_error returning to this function. */
   saved_error_buf = image->opaque->error_buf;
   result = setjmp(safe_jmpbuf) == 0;

   if (result != 0)
   {

      image->opaque->error_buf = safe_jmpbuf;
      result = function(arg);
   }

   image->opaque->error_buf = saved_error_buf;

   /* And do the cleanup prior to any failure return. */
   if (result == 0)
      png_image_free(image);

   return result;
}