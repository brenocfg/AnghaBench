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
typedef  int u32 ;
struct TYPE_2__ {int color_fmt; int depth; int bpp; int x; int y; int bpl; int vidadr; int sheight; int width; int height; } ;
struct saa7146 {TYPE_1__ win; } ;

/* Variables and functions */
 scalar_t__ CurrentMode ; 
 int /*<<< orphan*/  SAA7146_BASE_EVEN1 ; 
 int /*<<< orphan*/  SAA7146_BASE_ODD1 ; 
 int /*<<< orphan*/  SAA7146_CLIP_FORMAT_CTRL ; 
 int /*<<< orphan*/  SAA7146_HPS_H_PRESCALE ; 
 int /*<<< orphan*/  SAA7146_HPS_H_SCALE ; 
 int /*<<< orphan*/  SAA7146_HPS_V_GAIN ; 
 int /*<<< orphan*/  SAA7146_HPS_V_SCALE ; 
 int /*<<< orphan*/  SAA7146_MC2 ; 
 int SAA7146_MC2_UPLD_DMA1 ; 
 int SAA7146_MC2_UPLD_HPS_H ; 
 int SAA7146_MC2_UPLD_HPS_V ; 
 int /*<<< orphan*/  SAA7146_PAGE1 ; 
 int /*<<< orphan*/  SAA7146_PITCH1 ; 
 int /*<<< orphan*/  SAA7146_PROT_ADDR1 ; 
 scalar_t__ VIDEO_MODE_NTSC ; 
 size_t VIDEO_PALETTE_RGB555 ; 
 size_t* bpp2fmt ; 
 int* h_prescale ; 
 int* palette2fmt ; 
 int /*<<< orphan*/  saawrite (int,int /*<<< orphan*/ ) ; 
 int* v_gain ; 

__attribute__((used)) static void saa7146_set_winsize(struct saa7146 *saa)
{
	u32 format;
	int offset, yacl, ysci;
	saa->win.color_fmt = format =
	    (saa->win.depth == 15) ? palette2fmt[VIDEO_PALETTE_RGB555] :
	    palette2fmt[bpp2fmt[(saa->win.bpp - 1) & 3]];
	offset = saa->win.x * saa->win.bpp + saa->win.y * saa->win.bpl;
	saawrite(saa->win.vidadr + offset, SAA7146_BASE_EVEN1);
	saawrite(saa->win.vidadr + offset + saa->win.bpl, SAA7146_BASE_ODD1);
	saawrite(saa->win.bpl * 2, SAA7146_PITCH1);
	saawrite(saa->win.vidadr + saa->win.bpl * saa->win.sheight,
		 SAA7146_PROT_ADDR1);
	saawrite(0, SAA7146_PAGE1);
	saawrite(format | 0x60, SAA7146_CLIP_FORMAT_CTRL);
	offset = (704 / (saa->win.width - 1)) & 0x3f;
	saawrite(h_prescale[offset], SAA7146_HPS_H_PRESCALE);
	offset = (720896 / saa->win.width) / (offset + 1);
	saawrite((offset << 12) | 0x0c, SAA7146_HPS_H_SCALE);
	if (CurrentMode == VIDEO_MODE_NTSC) {
		yacl = /*(480 / saa->win.height - 1) & 0x3f */ 0;
		ysci = 1024 - (saa->win.height * 1024 / 480);
	} else {
		yacl = /*(576 / saa->win.height - 1) & 0x3f */ 0;
		ysci = 1024 - (saa->win.height * 1024 / 576);
	}
	saawrite((1 << 31) | (ysci << 21) | (yacl << 15), SAA7146_HPS_V_SCALE);
	saawrite(v_gain[yacl], SAA7146_HPS_V_GAIN);
	saawrite(((SAA7146_MC2_UPLD_DMA1 | SAA7146_MC2_UPLD_HPS_V |
		SAA7146_MC2_UPLD_HPS_H) << 16) | (SAA7146_MC2_UPLD_DMA1 |
		SAA7146_MC2_UPLD_HPS_V | SAA7146_MC2_UPLD_HPS_H), SAA7146_MC2);
}