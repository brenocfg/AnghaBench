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
struct snd_akm4xxx {int type; } ;

/* Variables and functions */
#define  SND_AK4355 133 
#define  SND_AK4358 132 
#define  SND_AK4381 131 
#define  SND_AK4524 130 
#define  SND_AK4528 129 
#define  SND_AK4529 128 
 int /*<<< orphan*/  ak435X_reset (struct snd_akm4xxx*,int,int) ; 
 int /*<<< orphan*/  ak4381_reset (struct snd_akm4xxx*,int) ; 
 int /*<<< orphan*/  ak4524_reset (struct snd_akm4xxx*,int) ; 

void snd_akm4xxx_reset(struct snd_akm4xxx *ak, int state)
{
	switch (ak->type) {
	case SND_AK4524:
	case SND_AK4528:
		ak4524_reset(ak, state);
		break;
	case SND_AK4529:
		/* FIXME: needed for ak4529? */
		break;
	case SND_AK4355:
		ak435X_reset(ak, state, 0x0b);
		break;
	case SND_AK4358:
		ak435X_reset(ak, state, 0x10);
		break;
	case SND_AK4381:
		ak4381_reset(ak, state);
		break;
	default:
		break;
	}
}