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
typedef  int /*<<< orphan*/  blip_t ;
struct TYPE_2__ {int frame_rate; int /*<<< orphan*/  sample_rate; } ;

/* Variables and functions */
 double PCM_SCYCLES_RATIO ; 
 int SCD_CLOCK ; 
 int SCYCLES_PER_LINE ; 
 int /*<<< orphan*/ ** blip ; 
 int /*<<< orphan*/  blip_set_rates (int /*<<< orphan*/ *,double,int /*<<< orphan*/ ) ; 
 TYPE_1__ snd ; 
 scalar_t__ vdp_pal ; 

void pcm_init(blip_t* left, blip_t* right)
{
  /* number of SCD master clocks run per second */
  double mclk = snd.frame_rate ? (SCYCLES_PER_LINE * (vdp_pal ? 313 : 262) * snd.frame_rate) : SCD_CLOCK;

  /* PCM chips is running at original rate and is synchronized with SUB-CPU  */
  /* Chip output is resampled to desired rate using Blip Buffer. */
  blip[0] = left;
  blip[1] = right;
  blip_set_rates(left, mclk / PCM_SCYCLES_RATIO, snd.sample_rate);
  blip_set_rates(right, mclk / PCM_SCYCLES_RATIO, snd.sample_rate);
}