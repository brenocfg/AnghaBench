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
typedef  scalar_t__ png_structp ;
typedef  char* png_const_charp ;
typedef  int /*<<< orphan*/  Throw ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
png_cexcept_error(png_structp png_ptr, png_const_charp msg)
{
   if(png_ptr)
     ;
#ifdef PNG_CONSOLE_IO_SUPPORTED
   fprintf(stderr, "libpng error: %s\n", msg);
#endif
   {
      Throw msg;
   }
}