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
struct TYPE_3__ {int brightness; int contrast; } ;
struct TYPE_4__ {TYPE_1__ tvo_params; } ;
struct matrox_fb_info {TYPE_2__ altout; } ;

/* Variables and functions */
 int BLMIN ; 
 int /*<<< orphan*/  WLMAX ; 
 int max (int const,int) ; 
 int min (int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void g450_compute_bwlevel(const struct matrox_fb_info *minfo, int *bl,
				 int *wl)
{
	const int b = minfo->altout.tvo_params.brightness + BLMIN;
	const int c = minfo->altout.tvo_params.contrast;

	*bl = max(b - c, BLMIN);
	*wl = min(b + c, WLMAX);
}