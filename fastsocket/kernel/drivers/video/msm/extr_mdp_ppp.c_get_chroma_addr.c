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
typedef  int uint32_t ;
struct mdp_rect {int x; int y; } ;
struct mdp_img {int width; int height; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 scalar_t__ IS_PSEUDOPLNR (int /*<<< orphan*/ ) ; 
 int Y_TO_CRCB_RATIO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_chroma_addr(struct mdp_img *img, struct mdp_rect *rect,
			    uint32_t base, uint32_t bpp, uint32_t cfg,
			    uint32_t *addr, uint32_t *ystride)
{
	uint32_t compress_v = Y_TO_CRCB_RATIO(img->format);
	uint32_t compress_h = 2;
	uint32_t  offset;

	if (IS_PSEUDOPLNR(img->format)) {
		offset = (rect->x / compress_h) * compress_h;
		offset += rect->y == 0 ? 0 :
			  ((rect->y + 1) / compress_v) * img->width;
		*addr = base + (img->width * img->height * bpp);
		*addr += offset * bpp;
		*ystride |= *ystride << 16;
	} else {
		*addr = 0;
	}
}