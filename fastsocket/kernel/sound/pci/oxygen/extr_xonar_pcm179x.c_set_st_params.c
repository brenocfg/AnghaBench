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
struct snd_pcm_hw_params {int dummy; } ;
struct oxygen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  set_pcm1796_params (struct oxygen*,struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  update_cs2000_rate (struct oxygen*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_st_params(struct oxygen *chip,
			  struct snd_pcm_hw_params *params)
{
	update_cs2000_rate(chip, params_rate(params));
	set_pcm1796_params(chip, params);
}