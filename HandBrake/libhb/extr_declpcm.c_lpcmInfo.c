#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int offset; int nchannels; int samplerate; int sample_size; int duration; int nchunks; int nsamples; int size; scalar_t__ next_pts; int /*<<< orphan*/  scr_sequence; } ;
typedef  TYPE_2__ hb_work_private_t ;
struct TYPE_9__ {TYPE_2__* private_data; } ;
typedef  TYPE_3__ hb_work_object_t ;
struct TYPE_7__ {scalar_t__ start; int /*<<< orphan*/  scr_sequence; } ;
struct TYPE_10__ {int* data; int size; TYPE_1__ s; } ;
typedef  TYPE_4__ hb_buffer_t ;

/* Variables and functions */
 scalar_t__ AV_NOPTS_VALUE ; 
 int HB_DVD_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  hb_log (char*,int) ; 
 int* hdr2samplerate ; 
 int* hdr2samplesize ; 

__attribute__((used)) static void lpcmInfo( hb_work_object_t *w, hb_buffer_t *in )
{
    hb_work_private_t * pv = w->private_data;

    /*
     * LPCM packets have a 7 byte header (the substream id is stripped off
     * before we get here so it's numbered -1 below)::
     * byte -1  Substream id
     * byte 0   Number of frames that begin in this packet
     *          (last frame may finish in next packet)
     * byte 1,2 offset to first frame that begins in this packet (not including hdr)
     * byte 3:
     *   bits 0-4  continuity counter (increments modulo 20)
     *   bit   5   reserved
     *   bit   6   audio mute on/off
     *   bit   7   audio emphasis on/off
     * byte 4:
     *   bits 0-2  #channels - 1 (e.g., stereo = 1)
     *   bit   3   reserved
     *   bits 4-5  sample rate (0=48K,1=96K,2=44.1K,3=32K)
     *   bits 6-7  bits per sample (0=16 bit, 1=20 bit, 2=24 bit)
     * byte 5   Dynamic range control (0x80 = off)
     *
     * The audio is viewed as "frames" of 150 90KHz ticks each (80 samples @ 48KHz).
     * The frames are laid down continuously without regard to MPEG packet
     * boundaries. E.g., for 48KHz stereo, the first packet will contain 6
     * frames plus the start of the 7th, the second packet will contain the
     * end of the 7th, 8-13 & the start of 14, etc. The frame structure is
     * important because the PTS on the packet gives the time of the first
     * frame that starts in the packet *NOT* the time of the first sample
     * in the packet. Also samples get split across packet boundaries
     * so we can't assume that we can consume all the data in one packet
     * on every call to the work routine.
     */
    pv->offset = ( ( in->data[1] << 8 ) | in->data[2] ) + 2;
    if ( pv->offset >= HB_DVD_READ_BUFFER_SIZE )
    {
        hb_log( "declpcm: illegal frame offset %d", pv->offset );
        pv->offset = 2; /*XXX*/
    }
    pv->nchannels   = ( in->data[4] & 7 ) + 1;
    pv->samplerate  = hdr2samplerate[ ( in->data[4] >> 4 ) & 0x3 ];
    pv->sample_size = hdr2samplesize[in->data[4] >> 6];

    // 20 and 24 bit lpcm is always encoded in sample pairs.  So take this
    // into account when computing sizes.
    int chunk_size = pv->sample_size / 8;
    int samples_per_chunk = 1;

    switch( pv->sample_size )
    {
        case 20:
            chunk_size = 5;
            samples_per_chunk = 2;
            break;
        case 24:
            chunk_size = 6;
            samples_per_chunk = 2;
            break;
    }

    /*
     * PCM frames have a constant duration (150 90KHz ticks).
     * We need to convert that to the amount of data expected.  It's the
     * duration divided by the sample rate (to get #samples) times the number
     * of channels times the bits per sample divided by 8 to get bytes.
     * (we have to compute in bits because 20 bit samples are not an integral
     * number of bytes). We do all the multiplies first then the divides to
     * avoid truncation errors.
     */
    /*
     * Don't trust the number of frames given in the header.  We've seen
     * streams for which this is incorrect, and it can be computed.
     * pv->duration = in->data[0] * 150;
     */
    int chunks = ( in->size - pv->offset ) / chunk_size;
    int samples = chunks * samples_per_chunk;

    // Calculate number of frames that start in this packet
    int frames = ( 90000 * samples / ( pv->samplerate * pv->nchannels ) +
                   149 ) / 150;

    pv->duration = frames * 150;
    pv->nchunks =  ( pv->duration * pv->nchannels * pv->samplerate +
                    samples_per_chunk - 1 ) / ( 90000 * samples_per_chunk );
    pv->nsamples = ( pv->duration * pv->samplerate ) / 90000;
    pv->size = pv->nchunks * chunk_size;

    if (in->s.start != AV_NOPTS_VALUE)
    {
        pv->next_pts     = in->s.start;
    }
    pv->scr_sequence = in->s.scr_sequence;
}