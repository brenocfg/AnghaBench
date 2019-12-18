#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {TYPE_1__* list; } ;
struct TYPE_18__ {TYPE_2__ pes; int /*<<< orphan*/  ts_flags; int /*<<< orphan*/  file_handle; } ;
typedef  TYPE_3__ hb_stream_t ;
struct TYPE_19__ {int stream_id; int stream_id_ext; int bd_substream_id; scalar_t__ header_len; } ;
typedef  TYPE_4__ hb_pes_info_t ;
struct TYPE_20__ {scalar_t__ size; scalar_t__ data; } ;
typedef  TYPE_5__ hb_buffer_t ;
typedef  int /*<<< orphan*/  bitbuf_t ;
struct TYPE_16__ {int /*<<< orphan*/  codec_param; int /*<<< orphan*/  codec; int /*<<< orphan*/  codec_name; int /*<<< orphan*/  stream_kind; } ;

/* Variables and functions */
 int A ; 
 int /*<<< orphan*/  AV_CODEC_ID_DTS ; 
 int /*<<< orphan*/  AV_CODEC_ID_TRUEHD ; 
 int /*<<< orphan*/  HB_ACODEC_DCA_HD ; 
 int /*<<< orphan*/  HB_ACODEC_FFTRUEHD ; 
 int /*<<< orphan*/  HB_DVD_READ_BUFFER_SIZE ; 
 int MAX_PS_PROBE_SIZE ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TS_HAS_PCR ; 
 int U ; 
 int /*<<< orphan*/  WORK_DECVOBSUB ; 
 int bits_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bits_init (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bits_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ decode_ps_map (TYPE_3__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fseeko (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_buffer_close (TYPE_5__**) ; 
 TYPE_5__* hb_buffer_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_deep_log (int,char*) ; 
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_log (char*) ; 
 int /*<<< orphan*/  hb_parse_ps (TYPE_3__*,scalar_t__,scalar_t__,TYPE_4__*) ; 
 int hb_ps_read_packet (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  hb_stream_seek (TYPE_3__*,double) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int update_ps_streams (TYPE_3__*,int,int,int,int) ; 

__attribute__((used)) static void hb_ps_stream_find_streams(hb_stream_t *stream)
{
    int ii, jj;
    hb_buffer_t *buf  = hb_buffer_init(HB_DVD_READ_BUFFER_SIZE);

    fseeko( stream->file_handle, 0, SEEK_SET );
    // Scan beginning of file, then if no program stream map is found
    // seek to 20% and scan again since there's occasionally no
    // audio at the beginning (particularly for vobs).
    for ( ii = 0; ii < 2; ii++ )
    {
        for ( jj = 0; jj < MAX_PS_PROBE_SIZE; jj += buf->size )
        {
            int stream_type;
            int len;

            hb_pes_info_t pes_info;
            buf->size = 0;
            len = hb_ps_read_packet( stream, buf );
            if ( len == 0 )
            {
                // Must have reached EOF
                break;
            }
            if ( !hb_parse_ps( stream, buf->data, buf->size, &pes_info ) )
            {
                hb_deep_log( 2, "hb_ps_stream_find_streams: Error parsing PS packet");
                continue;
            }
            if ( pes_info.stream_id == 0xba )
            {
                stream->ts_flags |= TS_HAS_PCR;
            }
            else if ( pes_info.stream_id == 0xbc )
            {
                // program stream map
                // Note that if there is a program map, any
                // extrapolation that is made below based on
                // stream id may be overridden by entry in the map.
                if ( decode_ps_map( stream, buf->data, buf->size ) )
                {
                    hb_log("Found program stream map");
                    // Normally, we could quit here since the program
                    // stream map *should* map all streams. But once
                    // again Tivo breaks things by not always creating
                    // complete maps.  So continue processing...
                }
                else
                {
                    hb_error("Error parsing program stream map");
                }
            }
            else if ( ( pes_info.stream_id & 0xe0 ) == 0xc0 )
            {
                // MPeg audio (c0 - df)
                stream_type = 0x04;
                update_ps_streams( stream, pes_info.stream_id,
                                   pes_info.stream_id_ext, stream_type, -1 );
            }
            else if ( pes_info.stream_id == 0xbd )
            {
                int ssid = pes_info.bd_substream_id;
                // Add a potential audio stream
                // Check dvd substream id
                if ( ssid >= 0x20 && ssid <= 0x37 )
                {
                    int idx = update_ps_streams( stream, pes_info.stream_id,
                                            pes_info.bd_substream_id, 0, -1 );
                    stream->pes.list[idx].stream_kind = S;
                    stream->pes.list[idx].codec = WORK_DECVOBSUB;
                    strncpy(stream->pes.list[idx].codec_name,
                            "DVD Subtitle", 80);
                    continue;
                }
                if ( ssid >= 0x80 && ssid <= 0x87 )
                {
                    stream_type = 0x81; // ac3
                }
                else if ( ( ssid >= 0x88 && ssid <= 0x8f ) ||
                          ( ssid >= 0x98 && ssid <= 0x9f ) )
                {
                    // Could be either dts or dts-hd
                    // will have to probe to resolve
                    int idx = update_ps_streams( stream, pes_info.stream_id,
                                            pes_info.bd_substream_id, 0, U );
                    stream->pes.list[idx].codec = HB_ACODEC_DCA_HD;
                    stream->pes.list[idx].codec_param = AV_CODEC_ID_DTS;
                    continue;
                }
                else if ( ssid >= 0xa0 && ssid <= 0xaf )
                {
                    stream_type = 0x83; // lpcm
                    // This is flagged as an unknown stream type in
                    // st2codec because it can be either LPCM or
                    // BD TrueHD. In this case it is LPCM.
                    update_ps_streams( stream, pes_info.stream_id,
                                   pes_info.bd_substream_id, stream_type, A );
                    continue;
                }
                else if ( ssid >= 0xb0 && ssid <= 0xbf )
                {
                    // HD-DVD TrueHD
                    int idx = update_ps_streams( stream, pes_info.stream_id,
                                            pes_info.bd_substream_id, 0, A );
                    stream->pes.list[idx].codec       = HB_ACODEC_FFTRUEHD;
                    stream->pes.list[idx].codec_param = AV_CODEC_ID_TRUEHD;
                    continue;
                }
                else if ( ssid >= 0xc0 && ssid <= 0xcf )
                {
                    // HD-DVD uses this for both ac3 and eac3.
                    // Check ac3 bitstream_id to distinguish between them.
                    bitbuf_t bb;
                    bits_init(&bb, buf->data + pes_info.header_len,
                              buf->size - pes_info.header_len, 0);
                    int sync = bits_get(&bb, 16);
                    if ( sync == 0x0b77 )
                    {
                        bits_skip(&bb, 24);
                        int bsid = bits_get(&bb, 5);
                        if ( bsid <= 10 )
                        {
                            // ac3
                            stream_type = 0x81; // ac3
                        }
                        else
                        {
                            // eac3
                            stream_type = 0x87; // eac3
                        }
                    }
                    else
                    {
                        // Doesn't look like an ac3 stream.  Probe it.
                        stream_type = 0x00;
                    }
                }
                else
                {
                    // Unknown. Probe it.
                    stream_type = 0x00;
                }
                update_ps_streams( stream, pes_info.stream_id,
                                   pes_info.bd_substream_id, stream_type, -1 );
            }
            else if ( ( pes_info.stream_id & 0xf0 ) == 0xe0 )
            {
                // Normally this is MPEG video, but MPEG-1 PS streams
                // (which do not have a program stream map)  may use
                // this for other types of video.
                //
                // Also, the hddvd tards decided to use 0xe2 and 0xe3 for
                // h.264 video :( and the twits decided not to put a
                // program stream map in the stream :'(
                //
                // So set this to an unknown stream type and probe.
                stream_type = 0x00;
                update_ps_streams( stream, pes_info.stream_id,
                                   pes_info.stream_id_ext, stream_type, -1 );
            }
            else if ( pes_info.stream_id == 0xfd )
            {
                if ( pes_info.stream_id_ext == 0x55 ||
                     pes_info.stream_id_ext == 0x56 )
                {
                    // hddvd uses this for vc-1.
                    stream_type = 0xea;
                }
                else
                {
                    // mark as unknown and probe.
                    stream_type = 0x00;
                }
                update_ps_streams( stream, pes_info.stream_id,
                                   pes_info.stream_id_ext, stream_type, -1 );
            }
        }
        hb_stream_seek( stream, 0.2 );
    }
    hb_buffer_close( &buf );
}