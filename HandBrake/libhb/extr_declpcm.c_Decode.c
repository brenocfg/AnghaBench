#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {int nsamples; int nchannels; int alloc_size; int nchunks; int sample_size; int* frame; scalar_t__ next_pts; scalar_t__ duration; int /*<<< orphan*/  scr_sequence; scalar_t__ data; int /*<<< orphan*/  resample; int /*<<< orphan*/  samplerate; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_10__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
struct TYPE_8__ {scalar_t__ start; scalar_t__ duration; scalar_t__ stop; int /*<<< orphan*/  scr_sequence; } ;
struct TYPE_11__ {TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 TYPE_4__* hb_audio_resample (int /*<<< orphan*/ ,int const**,int) ; 
 int /*<<< orphan*/  hb_audio_resample_set_channel_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_audio_resample_set_sample_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hb_audio_resample_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/ * hdr2layout ; 
 scalar_t__ realloc (scalar_t__,int) ; 

__attribute__((used)) static hb_buffer_t *Decode( hb_work_object_t *w )
{
    hb_work_private_t *pv = w->private_data;
    hb_buffer_t *out;

    if (pv->nsamples == 0)
        return NULL;

    int size = pv->nsamples * pv->nchannels * sizeof( float );
    if (pv->alloc_size != size)
    {
        pv->data = realloc( pv->data, size );
        pv->alloc_size = size;
    }

    float *odat = (float *)pv->data;
    int count = pv->nchunks / pv->nchannels;

    switch( pv->sample_size )
    {
        case 16: // 2 byte, big endian, signed (the right shift sign extends)
        {
            uint8_t *frm = pv->frame;
            while ( count-- )
            {
                int cc;
                for( cc = 0; cc < pv->nchannels; cc++ )
                {
                    // Shifts below result in sign extension which gives
                    // us proper signed values. The final division adjusts
                    // the range to [-1.0 ... 1.0]
                    *odat++ = (float)( ( (int)( frm[0] << 24 ) >> 16 ) |
                                       frm[1] ) / 32768.0;
                    frm += 2;
                }
            }
        } break;
        case 20:
        {
            // There will always be 2 groups of samples.  A group is
            // a collection of samples that spans all channels.
            // The data for the samples is split.  The first 2 msb
            // bytes for all samples is encoded first, then the remaining
            // lsb bits are encoded.
            uint8_t *frm = pv->frame;
            while ( count-- )
            {
                int gg, cc;
                int shift = 4;
                uint8_t *lsb = frm + 4 * pv->nchannels;
                for( gg = 0; gg < 2; gg++ )
                {
                    for( cc = 0; cc < pv->nchannels; cc++ )
                    {
                        // Shifts below result in sign extension which gives
                        // us proper signed values. The final division adjusts
                        // the range to [-1.0 ... 1.0]
                        *odat = (float)( ( (int)( frm[0] << 24 ) >> 12 ) |
                                         ( frm[1] << 4 ) |
                                         ( ( ( lsb[0] >> shift ) & 0x0f ) ) ) /
                                       (16. * 32768.0);
                        odat++;
                        lsb += !shift;
                        shift ^= 4;
                        frm += 2;
                    }
                }
                frm = lsb;
            }
        } break;
        case 24:
        {
            // There will always be 2 groups of samples.  A group is
            // a collection of samples that spans all channels.
            // The data for the samples is split.  The first 2 msb
            // bytes for all samples is encoded first, then the remaining
            // lsb bits are encoded.
            uint8_t *frm = pv->frame;
            while ( count-- )
            {
                int gg, cc;
                uint8_t *lsb = frm + 4 * pv->nchannels;
                for( gg = 0; gg < 2; gg++ )
                {
                    for( cc = 0; cc < pv->nchannels; cc++ )
                    {
                        // Shifts below result in sign extension which gives
                        // us proper signed values. The final division adjusts
                        // the range to [-1.0 ... 1.0]
                        *odat++ = (float)( ( (int)( frm[0] << 24 ) >> 8 ) |
                                           ( frm[1] << 8 ) | lsb[0] ) /
                                  (256. * 32768.0);
                        frm += 2;
                        lsb++;
                    }
                }
                frm = lsb;
            }
        } break;
    }

    hb_audio_resample_set_channel_layout(pv->resample,
                                         hdr2layout[pv->nchannels - 1]);
    hb_audio_resample_set_sample_rate(pv->resample,
                                      pv->samplerate);
    if (hb_audio_resample_update(pv->resample))
    {
        hb_log("declpcm: hb_audio_resample_update() failed");
        return NULL;
    }
    out = hb_audio_resample(pv->resample, (const uint8_t **)&pv->data,
                            pv->nsamples);

    if (out != NULL)
    {
        out->s.start         = pv->next_pts;
        out->s.duration      = pv->duration;
        if (pv->next_pts != (int64_t)AV_NOPTS_VALUE)
        {
            pv->next_pts        += pv->duration;
            out->s.stop          = pv->next_pts;
        }
        out->s.scr_sequence  = pv->scr_sequence;
    }
    return out;
}