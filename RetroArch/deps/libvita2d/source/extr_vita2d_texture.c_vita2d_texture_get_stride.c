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
typedef  int /*<<< orphan*/  vita2d_texture ;

/* Variables and functions */
 int tex_format_to_bytespp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vita2d_texture_get_format (int /*<<< orphan*/  const*) ; 
 int vita2d_texture_get_width (int /*<<< orphan*/  const*) ; 

unsigned int vita2d_texture_get_stride(const vita2d_texture *texture)
{
	return ((vita2d_texture_get_width(texture) + 7) & ~7)
		* tex_format_to_bytespp(vita2d_texture_get_format(texture));
}