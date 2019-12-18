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
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx20442_audio_map ; 
 int /*<<< orphan*/  cx20442_dapm_widgets ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_widgets (struct snd_soc_codec*) ; 

__attribute__((used)) static int cx20442_add_widgets(struct snd_soc_codec *codec)
{
	snd_soc_dapm_new_controls(codec, cx20442_dapm_widgets,
				  ARRAY_SIZE(cx20442_dapm_widgets));

	snd_soc_dapm_add_routes(codec, cx20442_audio_map,
				ARRAY_SIZE(cx20442_audio_map));

	snd_soc_dapm_new_widgets(codec);
	return 0;
}