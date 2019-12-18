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
struct tremolo_core {int maxindex; double* wavetable; scalar_t__ index; } ;

/* Variables and functions */
 int M_PI ; 
 int fabs (double const) ; 
 int fmod (double,double) ; 
 double* malloc (int) ; 
 int /*<<< orphan*/  memset (double*,int /*<<< orphan*/ ,int) ; 
 double sin (int) ; 

__attribute__((used)) static void tremolocore_init(struct tremolo_core *core,float depth,int samplerate,float freq)
{
      const double offset = 1. - depth / 2.;
      unsigned i;
      double env;
      core->index = 0;
	core->maxindex = samplerate/freq;
	core->wavetable = malloc(core->maxindex*sizeof(float));
	memset(core->wavetable, 0, core->maxindex * sizeof(float));
	for (i = 0; i < core->maxindex; i++) {
	env = freq * i / samplerate;
	env = sin((M_PI*2) * fmod(env + 0.25, 1.0));
	core->wavetable[i] = env * (1 - fabs(offset)) + offset;
      }
}