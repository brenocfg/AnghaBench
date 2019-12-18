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
struct mdp_rect {int /*<<< orphan*/  w; int /*<<< orphan*/  h; } ;
struct mdp_img {int /*<<< orphan*/  format; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int IMG_LEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ IS_PSEUDOPLNR (int /*<<< orphan*/ ) ; 
 int Y_TO_CRCB_RATIO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_len(struct mdp_img *img, struct mdp_rect *rect, uint32_t bpp,
		    uint32_t *len0, uint32_t *len1)
{
	*len0 = IMG_LEN(rect->h, img->width, rect->w, bpp);
	if (IS_PSEUDOPLNR(img->format))
		*len1 = *len0/Y_TO_CRCB_RATIO(img->format);
	else
		*len1 = 0;
}