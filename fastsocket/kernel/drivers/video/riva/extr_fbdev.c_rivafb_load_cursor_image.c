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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/ * CURSOR; } ;
struct riva_par {TYPE_1__ riva; } ;

/* Variables and functions */
 int MAX_CURS ; 
 int le16_to_cpu (int) ; 
 int /*<<< orphan*/  reverse_order (int*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rivafb_load_cursor_image(struct riva_par *par, u8 *data8,
				     u16 bg, u16 fg, u32 w, u32 h)
{
	int i, j, k = 0;
	u32 b, tmp;
	u32 *data = (u32 *)data8;
	bg = le16_to_cpu(bg);
	fg = le16_to_cpu(fg);

	w = (w + 1) & ~1;

	for (i = 0; i < h; i++) {
		b = *data++;
		reverse_order(&b);
		
		for (j = 0; j < w/2; j++) {
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
			writel(tmp, &par->riva.CURSOR[k++]);
		}
		k += (MAX_CURS - w)/2;
	}
}