#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  double uint8_t ;
struct TYPE_9__ {int scale; TYPE_3__** fft_data; TYPE_2__* phase; TYPE_1__* magnitude; } ;
struct TYPE_8__ {float re; float im; } ;
struct TYPE_7__ {int* linesize; scalar_t__* data; } ;
struct TYPE_6__ {int* linesize; scalar_t__* data; } ;
typedef  TYPE_4__ SpectrumSynthContext ;

/* Variables and functions */
#define  LINEAR 129 
#define  LOG 128 
 double const M_PI ; 
 scalar_t__ UINT8_MAX ; 
 int /*<<< orphan*/  av_assert0 (int /*<<< orphan*/ ) ; 
 float cos (float) ; 
 float ff_exp10 (int) ; 
 float sin (float) ; 

__attribute__((used)) static void read8_fft_bin(SpectrumSynthContext *s,
                          int x, int y, int f, int ch)
{
    const int m_linesize = s->magnitude->linesize[0];
    const int p_linesize = s->phase->linesize[0];
    const uint8_t *m = (uint8_t *)(s->magnitude->data[0] + y * m_linesize);
    const uint8_t *p = (uint8_t *)(s->phase->data[0] + y * p_linesize);
    float magnitude, phase;

    switch (s->scale) {
    case LINEAR:
        magnitude = m[x] / (double)UINT8_MAX;
        break;
    case LOG:
        magnitude = ff_exp10(((m[x] / (double)UINT8_MAX) - 1.) * 6.);
        break;
    default:
        av_assert0(0);
    }
    phase = ((p[x] / (double)UINT8_MAX) * 2. - 1.) * M_PI;

    s->fft_data[ch][f].re = magnitude * cos(phase);
    s->fft_data[ch][f].im = magnitude * sin(phase);
}