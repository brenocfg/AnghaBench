#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ submodel; int caps; scalar_t__ duplex; } ;
typedef  TYPE_1__ sb_devc ;

/* Variables and functions */
 int ES1688_CLOCK1 ; 
 int ES1688_CLOCK2 ; 
 int ES18XX_CLOCK1 ; 
 int ES18XX_CLOCK2 ; 
 int SB_CAP_ES18XX_RATE ; 
 scalar_t__ SUBMDL_ES1888 ; 
 int /*<<< orphan*/  ess_calc_best_speed (int,int,int,int,int*,int*) ; 
 int ess_calc_div (int,int,int*,int*) ; 

__attribute__((used)) static void ess_common_speed (sb_devc *devc, int *speedp, int *divp)
{
	int diff = 0, div;

	if (devc->duplex) {
		/*
		 * The 0x80 is important for the first audio channel
		 */
		if (devc->submodel == SUBMDL_ES1888) {
			div = 0x80 | ess_calc_div (795500, 256, speedp, &diff);
		} else {
			div = 0x80 | ess_calc_div (795500, 128, speedp, &diff);
		}
	} else if(devc->caps & SB_CAP_ES18XX_RATE) {
		if (devc->submodel == SUBMDL_ES1888) {
			ess_calc_best_speed(397700, 128, 795500, 256, 
						&div, speedp);
		} else {
			ess_calc_best_speed(ES18XX_CLOCK1, 128, ES18XX_CLOCK2, 256, 
						&div, speedp);
		}
	} else {
		if (*speedp > 22000) {
			div = 0x80 | ess_calc_div (ES1688_CLOCK1, 256, speedp, &diff);
		} else {
			div = 0x00 | ess_calc_div (ES1688_CLOCK2, 128, speedp, &diff);
		}
	}
	*divp = div;
}