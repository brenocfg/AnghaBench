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
struct nouveau_timer {int dummy; } ;
struct nouveau_device {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int MAX_HBLANK_OSC ; 
 int /*<<< orphan*/  NV_PRMCIO_INP0 ; 
 int /*<<< orphan*/  NV_PRMCIO_INP0__COLOR ; 
 struct nouveau_device* nouveau_dev (struct drm_device*) ; 
 struct nouveau_timer* nouveau_timer (struct nouveau_device*) ; 
 int /*<<< orphan*/  nouveau_timer_wait_eq (struct nouveau_timer*,int,int /*<<< orphan*/ ,int,int) ; 
 int nv_rd08 (struct nouveau_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int sample_load_twice(struct drm_device *dev, bool sense[2])
{
	struct nouveau_device *device = nouveau_dev(dev);
	struct nouveau_timer *ptimer = nouveau_timer(device);
	int i;

	for (i = 0; i < 2; i++) {
		bool sense_a, sense_b, sense_b_prime;
		int j = 0;

		/*
		 * wait for bit 0 clear -- out of hblank -- (say reg value 0x4),
		 * then wait for transition 0x4->0x5->0x4: enter hblank, leave
		 * hblank again
		 * use a 10ms timeout (guards against crtc being inactive, in
		 * which case blank state would never change)
		 */
		if (!nouveau_timer_wait_eq(ptimer, 10000000,
					   NV_PRMCIO_INP0__COLOR,
					   0x00000001, 0x00000000))
			return -EBUSY;
		if (!nouveau_timer_wait_eq(ptimer, 10000000,
					   NV_PRMCIO_INP0__COLOR,
					   0x00000001, 0x00000001))
			return -EBUSY;
		if (!nouveau_timer_wait_eq(ptimer, 10000000,
					   NV_PRMCIO_INP0__COLOR,
					   0x00000001, 0x00000000))
			return -EBUSY;

		udelay(100);
		/* when level triggers, sense is _LO_ */
		sense_a = nv_rd08(device, NV_PRMCIO_INP0) & 0x10;

		/* take another reading until it agrees with sense_a... */
		do {
			udelay(100);
			sense_b = nv_rd08(device, NV_PRMCIO_INP0) & 0x10;
			if (sense_a != sense_b) {
				sense_b_prime =
					nv_rd08(device, NV_PRMCIO_INP0) & 0x10;
				if (sense_b == sense_b_prime) {
					/* ... unless two consecutive subsequent
					 * samples agree; sense_a is replaced */
					sense_a = sense_b;
					/* force mis-match so we loop */
					sense_b = !sense_a;
				}
			}
		} while ((sense_a != sense_b) && ++j < MAX_HBLANK_OSC);

		if (j == MAX_HBLANK_OSC)
			/* with so much oscillation, default to sense:LO */
			sense[i] = false;
		else
			sense[i] = sense_a;
	}

	return 0;
}