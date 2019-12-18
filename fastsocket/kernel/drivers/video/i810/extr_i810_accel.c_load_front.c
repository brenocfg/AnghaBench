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
struct TYPE_2__ {int offset; } ;
struct i810fb_par {int pitch; TYPE_1__ fb; } ;
struct fb_info {struct i810fb_par* par; } ;

/* Variables and functions */
 int FLUSH ; 
 int FRONT_BUFFER ; 
 scalar_t__ IRING_PAD ; 
 int NOP ; 
 int PARSER ; 
 int /*<<< orphan*/  PUT_RING (int) ; 
 scalar_t__ begin_iring (struct fb_info*,scalar_t__) ; 
 int /*<<< orphan*/  end_iring (struct i810fb_par*) ; 

__attribute__((used)) static inline void load_front(int offset, struct fb_info *info)
{
	struct i810fb_par *par = info->par;

	if (begin_iring(info, 8 + IRING_PAD)) return;

	PUT_RING(PARSER | FLUSH);
	PUT_RING(NOP);

	end_iring(par);

	if (begin_iring(info, 8 + IRING_PAD)) return;

	PUT_RING(PARSER | FRONT_BUFFER | ((par->pitch >> 3) << 8));
	PUT_RING((par->fb.offset << 12) + offset);

	end_iring(par);
}