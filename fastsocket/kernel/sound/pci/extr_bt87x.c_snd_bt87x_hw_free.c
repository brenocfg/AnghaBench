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
struct snd_bt87x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_bt87x_free_risc (struct snd_bt87x*) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 
 struct snd_bt87x* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int snd_bt87x_hw_free(struct snd_pcm_substream *substream)
{
	struct snd_bt87x *chip = snd_pcm_substream_chip(substream);

	snd_bt87x_free_risc(chip);
	snd_pcm_lib_free_pages(substream);
	return 0;
}