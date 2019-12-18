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
struct snd_rme9652 {unsigned int control_register; int period_bytes; int hw_offsetmask; int max_jitter; } ;

/* Variables and functions */
 int RME9652_buf_pos ; 
 unsigned int RME9652_latency ; 
 int rme9652_decode_latency (unsigned int) ; 

__attribute__((used)) static inline void rme9652_compute_period_size(struct snd_rme9652 *rme9652)
{
	unsigned int i;

	i = rme9652->control_register & RME9652_latency;
	rme9652->period_bytes = 1 << ((rme9652_decode_latency(i) + 8));
	rme9652->hw_offsetmask = 
		(rme9652->period_bytes * 2 - 1) & RME9652_buf_pos;
	rme9652->max_jitter = 80;
}