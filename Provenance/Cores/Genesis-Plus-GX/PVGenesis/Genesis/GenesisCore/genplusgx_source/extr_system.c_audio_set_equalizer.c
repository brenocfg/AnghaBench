#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ hg; scalar_t__ mg; scalar_t__ lg; int /*<<< orphan*/  high_freq; int /*<<< orphan*/  low_freq; } ;
struct TYPE_6__ {double lg; double mg; double hg; } ;
struct TYPE_5__ {int /*<<< orphan*/  sample_rate; } ;

/* Variables and functions */
 TYPE_4__ config ; 
 TYPE_2__ eq ; 
 int /*<<< orphan*/  init_3band_state (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ snd ; 

void audio_set_equalizer(void)
{
  init_3band_state(&eq,config.low_freq,config.high_freq,snd.sample_rate);
  eq.lg = (double)(config.lg) / 100.0;
  eq.mg = (double)(config.mg) / 100.0;
  eq.hg = (double)(config.hg) / 100.0;
}