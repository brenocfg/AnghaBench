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
typedef  int /*<<< orphan*/  png_uint_32 ;
struct TYPE_4__ {char const* file_name; int stride_extra; int /*<<< orphan*/  opts; int /*<<< orphan*/  image; } ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int /*<<< orphan*/  freeimage (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void initimage(Image *image, png_uint_32 opts, const char *file_name,
   int stride_extra)
{
   freeimage(image);
   memset(&image->image, 0, sizeof image->image);
   image->opts = opts;
   image->file_name = file_name;
   image->stride_extra = stride_extra;
}