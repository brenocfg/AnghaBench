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
struct TYPE_2__ {int phadadj; } ;

/* Variables and functions */
 int DEFAULT_PHAD_QVGA ; 
 int /*<<< orphan*/  PHACTRL_ADRS ; 
 int PHACTRL_PHASE_MANUAL ; 
 int /*<<< orphan*/  corgi_ssp_lcdtg_send (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ sharpsl_param ; 

__attribute__((used)) static void lcdtg_set_phadadj(int mode)
{
	int adj;
	switch(mode) {
		case 480:
		case 640:
			/* Setting for VGA */
			adj = sharpsl_param.phadadj;
			if (adj < 0) {
				adj = PHACTRL_PHASE_MANUAL;
			} else {
				adj = ((adj & 0x0f) << 1) | PHACTRL_PHASE_MANUAL;
			}
			break;
		case 240:
		case 320:
		default:
			/* Setting for QVGA */
			adj = (DEFAULT_PHAD_QVGA << 1) | PHACTRL_PHASE_MANUAL;
			break;
	}

	corgi_ssp_lcdtg_send(PHACTRL_ADRS, adj);
}