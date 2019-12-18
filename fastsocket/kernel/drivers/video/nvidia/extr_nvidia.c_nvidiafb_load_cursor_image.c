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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct nvidia_par {int /*<<< orphan*/ * CURSOR; } ;

/* Variables and functions */
 int MAX_CURS ; 
 int /*<<< orphan*/  NV_WR32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reverse_order (int*) ; 

__attribute__((used)) static void nvidiafb_load_cursor_image(struct nvidia_par *par, u8 * data8,
				       u16 bg, u16 fg, u32 w, u32 h)
{
	u32 *data = (u32 *) data8;
	int i, j, k = 0;
	u32 b, tmp;

	w = (w + 1) & ~1;

	for (i = 0; i < h; i++) {
		b = *data++;
		reverse_order(&b);

		for (j = 0; j < w / 2; j++) {
			tmp = 0;
#if defined (__BIG_ENDIAN)
			tmp = (b & (1 << 31)) ? fg << 16 : bg << 16;
			b <<= 1;
			tmp |= (b & (1 << 31)) ? fg : bg;
			b <<= 1;
#else
			tmp = (b & 1) ? fg : bg;
			b >>= 1;
			tmp |= (b & 1) ? fg << 16 : bg << 16;
			b >>= 1;
#endif
			NV_WR32(&par->CURSOR[k++], 0, tmp);
		}
		k += (MAX_CURS - w) / 2;
	}
}