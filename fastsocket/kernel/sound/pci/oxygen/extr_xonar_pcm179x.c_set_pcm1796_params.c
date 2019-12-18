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
struct xonar_pcm179x {int /*<<< orphan*/  current_rate; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct oxygen {struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  update_pcm1796_oversampling (struct oxygen*) ; 

__attribute__((used)) static void set_pcm1796_params(struct oxygen *chip,
			       struct snd_pcm_hw_params *params)
{
	struct xonar_pcm179x *data = chip->model_data;

	msleep(1);
	data->current_rate = params_rate(params);
	update_pcm1796_oversampling(chip);
}