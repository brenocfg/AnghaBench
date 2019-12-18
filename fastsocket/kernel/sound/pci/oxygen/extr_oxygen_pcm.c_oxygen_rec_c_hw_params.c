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
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct oxygen {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  OXYGEN_REC_FORMAT ; 
 int /*<<< orphan*/  OXYGEN_REC_FORMAT_C_MASK ; 
 int OXYGEN_REC_FORMAT_C_SHIFT ; 
 int oxygen_format (struct snd_pcm_hw_params*) ; 
 int oxygen_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  oxygen_write8_masked (struct oxygen*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct oxygen* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int oxygen_rec_c_hw_params(struct snd_pcm_substream *substream,
				  struct snd_pcm_hw_params *hw_params)
{
	struct oxygen *chip = snd_pcm_substream_chip(substream);
	int err;

	err = oxygen_hw_params(substream, hw_params);
	if (err < 0)
		return err;

	spin_lock_irq(&chip->reg_lock);
	oxygen_write8_masked(chip, OXYGEN_REC_FORMAT,
			     oxygen_format(hw_params) << OXYGEN_REC_FORMAT_C_SHIFT,
			     OXYGEN_REC_FORMAT_C_MASK);
	spin_unlock_irq(&chip->reg_lock);
	return 0;
}