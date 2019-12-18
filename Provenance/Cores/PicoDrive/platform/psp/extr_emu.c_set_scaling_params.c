#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* reg; } ;
struct TYPE_8__ {TYPE_1__ video; } ;
struct TYPE_7__ {double scale; double hscale40; double hscale32; } ;
struct TYPE_6__ {int x; int y; int z; int u; int v; } ;

/* Variables and functions */
 TYPE_4__ Pico ; 
 TYPE_3__ currentConfig ; 
 int fbimg_offs ; 
 TYPE_2__* g_vertices ; 

__attribute__((used)) static void set_scaling_params(void)
{
	int src_width, fbimg_width, fbimg_height, fbimg_xoffs, fbimg_yoffs, border_hack = 0;
	g_vertices[0].x = g_vertices[0].y =
	g_vertices[0].z = g_vertices[1].z = 0;

	fbimg_height = (int)(240.0 * currentConfig.scale + 0.5);
	if (Pico.video.reg[12] & 1) {
		fbimg_width = (int)(320.0 * currentConfig.scale * currentConfig.hscale40 + 0.5);
		src_width = 320;
	} else {
		fbimg_width = (int)(256.0 * currentConfig.scale * currentConfig.hscale32 + 0.5);
		src_width = 256;
	}

	if (fbimg_width  & 1) fbimg_width++;  // make even
	if (fbimg_height & 1) fbimg_height++;

	if (fbimg_width >= 480) {
		g_vertices[0].u = (fbimg_width-480)/2;
		g_vertices[1].u = src_width - (fbimg_width-480)/2 - 1;
		fbimg_width = 480;
		fbimg_xoffs = 0;
	} else {
		g_vertices[0].u = 0;
		g_vertices[1].u = src_width;
		fbimg_xoffs = 240 - fbimg_width/2;
	}
	if (fbimg_width > 320 && fbimg_width <= 480) border_hack = 1;

	if (fbimg_height >= 272) {
		g_vertices[0].v = (fbimg_height-272)/2;
		g_vertices[1].v = 240 - (fbimg_height-272)/2;
		fbimg_height = 272;
		fbimg_yoffs = 0;
	} else {
		g_vertices[0].v = 0;
		g_vertices[1].v = 240;
		fbimg_yoffs = 136 - fbimg_height/2;
	}

	g_vertices[1].x = fbimg_width;
	g_vertices[1].y = fbimg_height;
	if (fbimg_xoffs < 0) fbimg_xoffs = 0;
	if (fbimg_yoffs < 0) fbimg_yoffs = 0;
	if (border_hack) {
		g_vertices[0].u++;
		g_vertices[0].x++;
		g_vertices[1].u--;
		g_vertices[1].x--;
	}
	fbimg_offs = (fbimg_yoffs*512 + fbimg_xoffs) * 2; // dst is always 16bit

	/*
	lprintf("set_scaling_params:\n");
	lprintf("offs: %i, %i\n", fbimg_xoffs, fbimg_yoffs);
	lprintf("xy0, xy1: %i, %i; %i, %i\n", g_vertices[0].x, g_vertices[0].y, g_vertices[1].x, g_vertices[1].y);
	lprintf("uv0, uv1: %i, %i; %i, %i\n", g_vertices[0].u, g_vertices[0].v, g_vertices[1].u, g_vertices[1].v);
	*/
}