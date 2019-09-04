#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_8__ {int nfreqbands; int nchannels; TYPE_1__* bands; int /*<<< orphan*/ ** sample_buffer; int /*<<< orphan*/ * sample_size; } ;
struct TYPE_7__ {int nframesamples; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** lsb_sample_buffer; scalar_t__ lsb_section_size; } ;
typedef  TYPE_2__ DCAXllDecoder ;
typedef  TYPE_3__ DCAXllChSet ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_fast_malloc (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int chs_alloc_lsb_band_data(DCAXllDecoder *s, DCAXllChSet *c)
{
    int i, j, nsamples = 0;
    int32_t *ptr;

    // Determine number of frequency bands that have MSB/LSB split
    for (i = 0; i < c->nfreqbands; i++)
        if (c->bands[i].lsb_section_size)
            nsamples += s->nframesamples * c->nchannels;
    if (!nsamples)
        return 0;

    // Reallocate LSB sample buffer
    av_fast_malloc(&c->sample_buffer[1], &c->sample_size[1], nsamples * sizeof(int32_t));
    if (!c->sample_buffer[1])
        return AVERROR(ENOMEM);

    ptr = c->sample_buffer[1];
    for (i = 0; i < c->nfreqbands; i++) {
        if (c->bands[i].lsb_section_size) {
            for (j = 0; j < c->nchannels; j++) {
                c->bands[i].lsb_sample_buffer[j] = ptr;
                ptr += s->nframesamples;
            }
        } else {
            for (j = 0; j < c->nchannels; j++)
                c->bands[i].lsb_sample_buffer[j] = NULL;
        }
    }

    return 0;
}