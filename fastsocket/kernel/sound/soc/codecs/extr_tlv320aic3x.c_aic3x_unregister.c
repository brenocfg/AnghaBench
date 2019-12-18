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
struct aic3x_priv {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/ * aic3x_codec ; 
 int /*<<< orphan*/  aic3x_dai ; 
 int /*<<< orphan*/  aic3x_set_bias_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aic3x_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aic3x_unregister(struct aic3x_priv *aic3x)
{
	aic3x_set_bias_level(&aic3x->codec, SND_SOC_BIAS_OFF);

	snd_soc_unregister_dai(&aic3x_dai);
	snd_soc_unregister_codec(&aic3x->codec);

	kfree(aic3x);
	aic3x_codec = NULL;

	return 0;
}