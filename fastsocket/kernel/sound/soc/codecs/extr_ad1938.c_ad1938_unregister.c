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
struct ad1938_priv {int /*<<< orphan*/  codec; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/ * ad1938_codec ; 
 int /*<<< orphan*/  ad1938_dai ; 
 int /*<<< orphan*/  ad1938_set_bias_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ad1938_priv*) ; 
 int /*<<< orphan*/  snd_soc_unregister_codec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_unregister_dai (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ad1938_unregister(struct ad1938_priv *ad1938)
{
	ad1938_set_bias_level(&ad1938->codec, SND_SOC_BIAS_OFF);
	snd_soc_unregister_dai(&ad1938_dai);
	snd_soc_unregister_codec(&ad1938->codec);
	kfree(ad1938);
	ad1938_codec = NULL;
}