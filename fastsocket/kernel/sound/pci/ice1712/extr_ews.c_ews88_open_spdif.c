#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cs8403_bits; int /*<<< orphan*/  cs8403_stream_bits; } ;
struct snd_ice1712 {TYPE_1__ spdif; } ;

/* Variables and functions */

__attribute__((used)) static void ews88_open_spdif(struct snd_ice1712 *ice, struct snd_pcm_substream *substream)
{
	ice->spdif.cs8403_stream_bits = ice->spdif.cs8403_bits;
}