#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  descriptor; int /*<<< orphan*/  bpp; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y_origin; int /*<<< orphan*/  x_origin; } ;
struct TYPE_3__ {int /*<<< orphan*/  bpp; int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
struct tga_header {TYPE_2__ image_info; TYPE_1__ colormap_info; int /*<<< orphan*/  image_type; int /*<<< orphan*/  color_map_type; int /*<<< orphan*/  id_length; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TGA_READ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_header(FILE *fp, struct tga_header *header) {
    TGA_READ(fp, header->id_length);
    TGA_READ(fp, header->color_map_type);
    TGA_READ(fp, header->image_type);
    TGA_READ(fp, header->colormap_info.offset);
    TGA_READ(fp, header->colormap_info.length);
    TGA_READ(fp, header->colormap_info.bpp);
    TGA_READ(fp, header->image_info.x_origin);
    TGA_READ(fp, header->image_info.y_origin);
    TGA_READ(fp, header->image_info.width);
    TGA_READ(fp, header->image_info.height);
    TGA_READ(fp, header->image_info.bpp);
    TGA_READ(fp, header->image_info.descriptor);

    return 0;

read_fail:
    return -1;
}