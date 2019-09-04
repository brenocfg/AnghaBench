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
struct TYPE_9__ {int /*<<< orphan*/  (* rdft_calc ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_7__ {TYPE_1__** complex; } ;
struct TYPE_8__ {int channels; int nb_channels; float* output_buffer; TYPE_2__ fft; int /*<<< orphan*/  fft_size; TYPE_4__ rdft_ctx; } ;
struct TYPE_6__ {float re; float im; } ;
typedef  TYPE_3__ QDM2Context ;
typedef  int /*<<< orphan*/  FFTSample ;

/* Variables and functions */
 int FFALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qdm2_calculate_fft(QDM2Context *q, int channel, int sub_packet)
{
    const float gain = (q->channels == 1 && q->nb_channels == 2) ? 0.5f : 1.0f;
    float *out       = q->output_buffer + channel;
    int i;
    q->fft.complex[channel][0].re *= 2.0f;
    q->fft.complex[channel][0].im  = 0.0f;
    q->rdft_ctx.rdft_calc(&q->rdft_ctx, (FFTSample *)q->fft.complex[channel]);
    /* add samples to output buffer */
    for (i = 0; i < FFALIGN(q->fft_size, 8); i++) {
        out[0]           += q->fft.complex[channel][i].re * gain;
        out[q->channels] += q->fft.complex[channel][i].im * gain;
        out              += 2 * q->channels;
    }
}