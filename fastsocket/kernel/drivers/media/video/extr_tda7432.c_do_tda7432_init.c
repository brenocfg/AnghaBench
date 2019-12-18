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
struct v4l2_subdev {int dummy; } ;
struct tda7432 {int input; int volume; int muted; scalar_t__ loud; void* rr; void* rf; void* lr; void* lf; int /*<<< orphan*/  bass; int /*<<< orphan*/  treble; } ;

/* Variables and functions */
 void* TDA7432_ATTEN_0DB ; 
 int /*<<< orphan*/  TDA7432_BASS_0DB ; 
 int TDA7432_BASS_NORM ; 
 int TDA7432_BASS_SYM ; 
 int TDA7432_LD_ON ; 
 int TDA7432_STEREO_IN ; 
 int /*<<< orphan*/  TDA7432_TREBLE_0DB ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ loudness ; 
 int /*<<< orphan*/  tda7432_set (struct v4l2_subdev*) ; 
 struct tda7432* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static void do_tda7432_init(struct v4l2_subdev *sd)
{
	struct tda7432 *t = to_state(sd);

	v4l2_dbg(2, debug, sd, "In tda7432_init\n");

	t->input  = TDA7432_STEREO_IN |  /* Main (stereo) input   */
		    TDA7432_BASS_SYM  |  /* Symmetric bass cut    */
		    TDA7432_BASS_NORM;   /* Normal bass range     */
	t->volume =  0x3b ;				 /* -27dB Volume            */
	if (loudness)			 /* Turn loudness on?     */
		t->volume |= TDA7432_LD_ON;
	t->muted    = 1;
	t->treble   = TDA7432_TREBLE_0DB; /* 0dB Treble            */
	t->bass		= TDA7432_BASS_0DB; 	 /* 0dB Bass              */
	t->lf     = TDA7432_ATTEN_0DB;	 /* 0dB attenuation       */
	t->lr     = TDA7432_ATTEN_0DB;	 /* 0dB attenuation       */
	t->rf     = TDA7432_ATTEN_0DB;	 /* 0dB attenuation       */
	t->rr     = TDA7432_ATTEN_0DB;	 /* 0dB attenuation       */
	t->loud   = loudness;		 /* insmod parameter      */

	tda7432_set(sd);
}