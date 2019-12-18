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
struct snd_cs46xx {int dummy; } ;
struct dsp_scb_descriptor {int /*<<< orphan*/  parent_scb_ptr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  _dsp_unlink_scb (struct snd_cs46xx*,struct dsp_scb_descriptor*) ; 
 int /*<<< orphan*/  cs46xx_dsp_scb_set_volume (struct snd_cs46xx*,struct dsp_scb_descriptor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ snd_BUG_ON (int) ; 

int cs46xx_src_unlink(struct snd_cs46xx *chip, struct dsp_scb_descriptor * src)
{
	if (snd_BUG_ON(!src->parent_scb_ptr))
		return -EINVAL;

	/* mute SCB */
	cs46xx_dsp_scb_set_volume (chip,src,0,0);

	_dsp_unlink_scb (chip,src);

	return 0;
}