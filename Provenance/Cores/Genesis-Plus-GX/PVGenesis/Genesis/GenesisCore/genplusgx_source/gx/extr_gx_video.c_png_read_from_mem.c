#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  png_structp ;
typedef  int /*<<< orphan*/  png_size_t ;
struct TYPE_2__ {scalar_t__ offset; scalar_t__ buffer; } ;
typedef  TYPE_1__ png_image ;
typedef  int /*<<< orphan*/  png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ png_get_io_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void png_read_from_mem (png_structp png_ptr, png_bytep data, png_size_t length)
{
  png_image *image = (png_image *)png_get_io_ptr(png_ptr);

  /* copy data from image buffer */
  memcpy (data, image->buffer + image->offset, length);

  /* advance in the file */
  image->offset += length;
}