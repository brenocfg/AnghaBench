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
struct hdsp {int /*<<< orphan*/  control2_register; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDSP_9652_ENABLE_MIXER ; 
 int /*<<< orphan*/  HDSP_control2Reg ; 
 int /*<<< orphan*/  hdsp_write (struct hdsp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_hdsp_9652_enable_mixer (struct hdsp *hdsp)
{
        hdsp->control2_register |= HDSP_9652_ENABLE_MIXER;
	hdsp_write (hdsp, HDSP_control2Reg, hdsp->control2_register);
}