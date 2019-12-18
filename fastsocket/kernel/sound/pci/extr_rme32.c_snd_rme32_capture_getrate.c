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
struct rme32 {int rcreg; } ;

/* Variables and functions */
 scalar_t__ RME32_PRO_WITH_8414 (struct rme32*) ; 
 int RME32_RCR_BITPOS_F0 ; 
 int RME32_RCR_BITPOS_F1 ; 
 int RME32_RCR_BITPOS_F2 ; 
 int RME32_RCR_ERF ; 
 int RME32_RCR_LOCK ; 

__attribute__((used)) static int snd_rme32_capture_getrate(struct rme32 * rme32, int *is_adat)
{
	int n;

	*is_adat = 0;
	if (rme32->rcreg & RME32_RCR_LOCK) { 
                /* ADAT rate */
                *is_adat = 1;
	}
	if (rme32->rcreg & RME32_RCR_ERF) {
		return -1;
	}

        /* S/PDIF rate */
	n = ((rme32->rcreg >> RME32_RCR_BITPOS_F0) & 1) +
		(((rme32->rcreg >> RME32_RCR_BITPOS_F1) & 1) << 1) +
		(((rme32->rcreg >> RME32_RCR_BITPOS_F2) & 1) << 2);

	if (RME32_PRO_WITH_8414(rme32))
		switch (n) {	/* supporting the CS8414 */
		case 0:
		case 1:
		case 2:
			return -1;
		case 3:
			return 96000;
		case 4:
			return 88200;
		case 5:
			return 48000;
		case 6:
			return 44100;
		case 7:
			return 32000;
		default:
			return -1;
			break;
		} 
	else
		switch (n) {	/* supporting the CS8412 */
		case 0:
			return -1;
		case 1:
			return 48000;
		case 2:
			return 44100;
		case 3:
			return 32000;
		case 4:
			return 48000;
		case 5:
			return 44100;
		case 6:
			return 44056;
		case 7:
			return 32000;
		default:
			break;
		}
	return -1;
}