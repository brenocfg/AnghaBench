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
struct _riva_hw_state {int* attr; int* crtc; int* gra; int* seq; int misc_output; } ;
struct nvidia_par {struct _riva_hw_state ModeReg; } ;
struct fb_info {struct nvidia_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  NUM_CRT_REGS ; 
 int /*<<< orphan*/  NUM_GRC_REGS ; 
 int /*<<< orphan*/  memset (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvidia_init_vga(struct fb_info *info)
{
	struct nvidia_par *par = info->par;
	struct _riva_hw_state *state = &par->ModeReg;
	int i;

	for (i = 0; i < 0x10; i++)
		state->attr[i] = i;
	state->attr[0x10] = 0x41;
	state->attr[0x11] = 0xff;
	state->attr[0x12] = 0x0f;
	state->attr[0x13] = 0x00;
	state->attr[0x14] = 0x00;

	memset(state->crtc, 0x00, NUM_CRT_REGS);
	state->crtc[0x0a] = 0x20;
	state->crtc[0x17] = 0xe3;
	state->crtc[0x18] = 0xff;
	state->crtc[0x28] = 0x40;

	memset(state->gra, 0x00, NUM_GRC_REGS);
	state->gra[0x05] = 0x40;
	state->gra[0x06] = 0x05;
	state->gra[0x07] = 0x0f;
	state->gra[0x08] = 0xff;

	state->seq[0x00] = 0x03;
	state->seq[0x01] = 0x01;
	state->seq[0x02] = 0x0f;
	state->seq[0x03] = 0x00;
	state->seq[0x04] = 0x0e;

	state->misc_output = 0xeb;
}