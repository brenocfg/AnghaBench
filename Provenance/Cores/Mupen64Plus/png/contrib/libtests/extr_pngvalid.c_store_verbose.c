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
typedef  int /*<<< orphan*/  png_store ;
typedef  int /*<<< orphan*/  png_const_structp ;
typedef  char* png_const_charp ;

/* Variables and functions */
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  store_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
store_verbose(png_store *ps, png_const_structp pp, png_const_charp prefix,
   png_const_charp message)
{
   char buffer[512];

   if (prefix)
      fputs(prefix, stderr);

   (void)store_message(ps, pp, buffer, sizeof buffer, 0, message);
   fputs(buffer, stderr);
   fputc('\n', stderr);
}