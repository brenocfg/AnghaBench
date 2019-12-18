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
 int /*<<< orphan*/  analogue_routes ; 
 int /*<<< orphan*/  lineout1_diff_routes ; 
 int /*<<< orphan*/  lineout1_se_routes ; 
 int /*<<< orphan*/  lineout2_diff_routes ; 
 int /*<<< orphan*/  lineout2_se_routes ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wm_hubs_add_analogue_routes(struct snd_soc_codec *codec,
				int lineout1_diff, int lineout2_diff)
{
	snd_soc_dapm_add_routes(codec, analogue_routes,
				ARRAY_SIZE(analogue_routes));

	if (lineout1_diff)
		snd_soc_dapm_add_routes(codec,
					lineout1_diff_routes,
					ARRAY_SIZE(lineout1_diff_routes));
	else
		snd_soc_dapm_add_routes(codec,
					lineout1_se_routes,
					ARRAY_SIZE(lineout1_se_routes));

	if (lineout2_diff)
		snd_soc_dapm_add_routes(codec,
					lineout2_diff_routes,
					ARRAY_SIZE(lineout2_diff_routes));
	else
		snd_soc_dapm_add_routes(codec,
					lineout2_se_routes,
					ARRAY_SIZE(lineout2_se_routes));

	return 0;
}