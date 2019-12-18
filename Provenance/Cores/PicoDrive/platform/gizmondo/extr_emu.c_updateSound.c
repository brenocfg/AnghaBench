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

/* Variables and functions */
 scalar_t__ PsndOut ; 
 int snd_all_samples ; 
 scalar_t__ snd_cbuf_samples ; 
 scalar_t__ snd_cbuff ; 

__attribute__((used)) static void updateSound(int len)
{
	snd_all_samples += len / 2;
	PsndOut += len / 2;
	if (PsndOut - snd_cbuff >= snd_cbuf_samples)
	{
		//if (PsndOut - snd_cbuff != snd_cbuf_samples)
		//	stdbg("snd diff is %i, not %i", PsndOut - snd_cbuff, snd_cbuf_samples);
		PsndOut = snd_cbuff;
	}
}