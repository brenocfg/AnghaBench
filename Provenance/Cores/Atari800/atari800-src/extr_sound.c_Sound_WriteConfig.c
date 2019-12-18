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
struct TYPE_2__ {int freq; int sample_size; int frag_frames; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 TYPE_1__ Sound_desired ; 
 int Sound_enabled ; 
 int Sound_latency ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 

void Sound_WriteConfig(FILE *fp)
{
	fprintf(fp, "SOUND_ENABLED=%u\n", Sound_enabled);
	fprintf(fp, "SOUND_RATE=%u\n", Sound_desired.freq);
	fprintf(fp, "SOUND_BITS=%u\n", Sound_desired.sample_size * 8);
	fprintf(fp, "SOUND_FRAG_FRAMES=%u\n", Sound_desired.frag_frames);
#ifdef SYNCHRONIZED_SOUND
	fprintf(fp, "SOUND_LATENCY=%u\n", Sound_latency);
#endif /* SYNCHRONIZED_SOUND */
}