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
struct atmel_abdac {int /*<<< orphan*/ * substream; } ;

/* Variables and functions */
 struct atmel_abdac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int atmel_abdac_close(struct snd_pcm_substream *substream)
{
	struct atmel_abdac *dac = snd_pcm_substream_chip(substream);
	dac->substream = NULL;
	return 0;
}