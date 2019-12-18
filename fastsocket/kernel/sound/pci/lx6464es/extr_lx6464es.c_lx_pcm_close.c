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

/* Variables and functions */
 int /*<<< orphan*/  snd_printdd (char*) ; 

__attribute__((used)) static int lx_pcm_close(struct snd_pcm_substream *substream)
{
	int err = 0;
	snd_printdd("->lx_pcm_close\n");
	return err;
}