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
typedef  int u32 ;
struct htcp {int minRTT; int alpha; int beta; } ;

/* Variables and functions */
 int ALPHA_BASE ; 
 int HZ ; 
 int htcp_cong_time (struct htcp*) ; 
 int /*<<< orphan*/  max (int,unsigned int) ; 
 int min (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ use_rtt_scaling ; 

__attribute__((used)) static inline void htcp_alpha_update(struct htcp *ca)
{
	u32 minRTT = ca->minRTT;
	u32 factor = 1;
	u32 diff = htcp_cong_time(ca);

	if (diff > HZ) {
		diff -= HZ;
		factor = 1 + (10 * diff + ((diff / 2) * (diff / 2) / HZ)) / HZ;
	}

	if (use_rtt_scaling && minRTT) {
		u32 scale = (HZ << 3) / (10 * minRTT);

		/* clamping ratio to interval [0.5,10]<<3 */
		scale = min(max(scale, 1U << 2), 10U << 3);
		factor = (factor << 3) / scale;
		if (!factor)
			factor = 1;
	}

	ca->alpha = 2 * factor * ((1 << 7) - ca->beta);
	if (!ca->alpha)
		ca->alpha = ALPHA_BASE;
}