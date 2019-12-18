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
struct corgi_lcd {int dummy; } ;
struct TYPE_2__ {int phadadj; } ;

/* Variables and functions */
#define  CORGI_LCD_MODE_QVGA 129 
#define  CORGI_LCD_MODE_VGA 128 
 int DEFAULT_PHAD_QVGA ; 
 int /*<<< orphan*/  PHACTRL_ADRS ; 
 int PHACTRL_PHASE_MANUAL ; 
 int /*<<< orphan*/  corgi_ssp_lcdtg_send (struct corgi_lcd*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ sharpsl_param ; 

__attribute__((used)) static void lcdtg_set_phadadj(struct corgi_lcd *lcd, int mode)
{
	int adj;

	switch(mode) {
	case CORGI_LCD_MODE_VGA:
		/* Setting for VGA */
		adj = sharpsl_param.phadadj;
		adj = (adj < 0) ? PHACTRL_PHASE_MANUAL :
				  PHACTRL_PHASE_MANUAL | ((adj & 0xf) << 1);
		break;
	case CORGI_LCD_MODE_QVGA:
	default:
		/* Setting for QVGA */
		adj = (DEFAULT_PHAD_QVGA << 1) | PHACTRL_PHASE_MANUAL;
		break;
	}

	corgi_ssp_lcdtg_send(lcd, PHACTRL_ADRS, adj);
}