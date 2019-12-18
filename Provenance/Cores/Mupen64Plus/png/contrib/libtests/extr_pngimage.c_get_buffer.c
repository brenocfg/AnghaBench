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
struct buffer {int dummy; } ;
typedef  int /*<<< orphan*/  png_structp ;

/* Variables and functions */
 scalar_t__ png_get_io_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct buffer *
get_buffer(png_structp pp)
   /* Used from libpng callbacks to get the current buffer */
{
   return (struct buffer*)png_get_io_ptr(pp);
}