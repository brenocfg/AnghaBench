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
struct vc_data {int vc_cols; int vc_size_row; scalar_t__ vc_origin; } ;
struct fbcon_ops {int /*<<< orphan*/  (* bmove ) (struct vc_data*,struct fb_info*,int,int,int,int,int,int) ;} ;
struct fb_info {struct fbcon_ops* fbcon_par; } ;
struct display {int dummy; } ;

/* Variables and functions */
 unsigned short* advance_row (unsigned short*,int) ; 
 int /*<<< orphan*/  console_conditional_schedule () ; 
 unsigned short scr_readw (unsigned short*) ; 
 int /*<<< orphan*/  scr_writew (unsigned short,unsigned short*) ; 
 int /*<<< orphan*/  stub1 (struct vc_data*,struct fb_info*,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  stub2 (struct vc_data*,struct fb_info*,int,int,int,int,int,int) ; 

__attribute__((used)) static void fbcon_redraw_blit(struct vc_data *vc, struct fb_info *info,
			struct display *p, int line, int count, int ycount)
{
	int offset = ycount * vc->vc_cols;
	unsigned short *d = (unsigned short *)
	    (vc->vc_origin + vc->vc_size_row * line);
	unsigned short *s = d + offset;
	struct fbcon_ops *ops = info->fbcon_par;

	while (count--) {
		unsigned short *start = s;
		unsigned short *le = advance_row(s, 1);
		unsigned short c;
		int x = 0;

		do {
			c = scr_readw(s);

			if (c == scr_readw(d)) {
				if (s > start) {
					ops->bmove(vc, info, line + ycount, x,
						   line, x, 1, s-start);
					x += s - start + 1;
					start = s + 1;
				} else {
					x++;
					start++;
				}
			}

			scr_writew(c, d);
			console_conditional_schedule();
			s++;
			d++;
		} while (s < le);
		if (s > start)
			ops->bmove(vc, info, line + ycount, x, line, x, 1,
				   s-start);
		console_conditional_schedule();
		if (ycount > 0)
			line++;
		else {
			line--;
			/* NOTE: We subtract two lines from these pointers */
			s -= vc->vc_size_row;
			d -= vc->vc_size_row;
		}
	}
}