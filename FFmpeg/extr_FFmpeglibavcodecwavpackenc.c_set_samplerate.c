#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; TYPE_1__* avctx; } ;
typedef  TYPE_2__ WavPackEncodeContext ;
struct TYPE_4__ {scalar_t__ sample_rate; } ;

/* Variables and functions */
 int SRATE_LSB ; 
 scalar_t__* wv_rates ; 

__attribute__((used)) static void set_samplerate(WavPackEncodeContext *s)
{
    int i;

    for (i = 0; i < 15; i++) {
        if (wv_rates[i] == s->avctx->sample_rate)
            break;
    }

    s->flags = i << SRATE_LSB;
}