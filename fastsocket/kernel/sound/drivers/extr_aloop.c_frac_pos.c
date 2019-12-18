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
struct loopback_pcm {unsigned long long pcm_rate_shift; } ;

/* Variables and functions */
 unsigned int HZ ; 
 unsigned long long NO_PITCH ; 
 unsigned int div_u64 (unsigned long long,unsigned long long) ; 

__attribute__((used)) static inline unsigned int frac_pos(struct loopback_pcm *dpcm, unsigned int x)
{
	if (dpcm->pcm_rate_shift == NO_PITCH) {	/* no pitch */
		return x * HZ;
	} else {
		x = div_u64(dpcm->pcm_rate_shift * (unsigned long long)x * HZ,
			    NO_PITCH);
	}
	return x;
}