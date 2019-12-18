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
struct matrox_fb_info {int dummy; } ;

/* Variables and functions */
 int g450_isplllocked (struct matrox_fb_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g450_setpll (struct matrox_fb_info const*,unsigned int,unsigned int) ; 

__attribute__((used)) static int g450_testpll(const struct matrox_fb_info *minfo, unsigned int mnp,
			unsigned int pll)
{
	return g450_isplllocked(minfo, g450_setpll(minfo, mnp, pll));
}