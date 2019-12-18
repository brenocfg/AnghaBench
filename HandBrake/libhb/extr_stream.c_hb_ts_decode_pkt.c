#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int int64_t ;
struct TYPE_19__ {scalar_t__ packet_len; int /*<<< orphan*/  header_len; } ;
struct TYPE_25__ {int continuity; int* pkt_summary; int skipbad; int pes_info_valid; scalar_t__ packet_len; size_t pes_list; TYPE_16__ pes_info; int /*<<< orphan*/  packet_offset; TYPE_4__* buf; } ;
typedef  TYPE_6__ hb_ts_stream_t ;
struct TYPE_21__ {TYPE_1__* list; } ;
struct TYPE_24__ {int discontinuity; int found_pcr; int pcr; scalar_t__ last_timestamp; TYPE_6__* list; } ;
struct TYPE_26__ {int chapter; int ts_flags; TYPE_2__ pes; TYPE_5__ ts; int /*<<< orphan*/  frames; } ;
typedef  TYPE_7__ hb_stream_t ;
typedef  int /*<<< orphan*/  hb_buffer_t ;
typedef  int /*<<< orphan*/  hb_buffer_list_t ;
struct TYPE_22__ {int new_chap; } ;
struct TYPE_23__ {int size; int /*<<< orphan*/  data; TYPE_3__ s; } ;
struct TYPE_20__ {scalar_t__ stream_kind; } ;

/* Variables and functions */
 scalar_t__ P ; 
 int TS_HAS_PCR ; 
 scalar_t__ V ; 
 int /*<<< orphan*/ * flush_ts_streams (TYPE_7__*) ; 
 int /*<<< orphan*/ * generate_output_data (TYPE_7__*,int) ; 
 int /*<<< orphan*/  hb_buffer_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_buffer_list_clear (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_parse_ps (TYPE_7__*,int /*<<< orphan*/ ,int,TYPE_16__*) ; 
 int /*<<< orphan*/  hb_ts_stream_append_pkt (TYPE_7__*,int,int const*,int) ; 
 int index_of_pid (TYPE_7__*,int) ; 
 scalar_t__ memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int pes_timestamp (int const*) ; 
 int /*<<< orphan*/  ts_err (TYPE_7__*,int,char*,...) ; 
 int ts_index_of_video (TYPE_7__*) ; 
 scalar_t__ ts_stream_kind (TYPE_7__*,int) ; 
 int /*<<< orphan*/  ts_warn (TYPE_7__*,char*,int,int) ; 

hb_buffer_t * hb_ts_decode_pkt( hb_stream_t *stream, const uint8_t * pkt,
                                int chapter, int discontinuity )
{
    /*
     * stash the output buffer pointer in our stream so we don't have to
     * pass it & its original value to everything we call.
     */
    int video_index = ts_index_of_video(stream);
    int curstream;
    hb_buffer_t *buf = NULL;
    hb_buffer_list_t list;

    hb_buffer_list_clear(&list);

    if (chapter > 0)
    {
        stream->chapter = chapter;
    }
    if (discontinuity)
    {
        // If there is a discontinuity, flush all data
        buf = flush_ts_streams(stream);
        hb_buffer_list_append(&list, buf);

        stream->ts.discontinuity = 1;
    }

    /* This next section validates the packet */

    // Get pid and use it to find stream state.
    int pid = ((pkt[1] & 0x1F) << 8) | pkt[2];
    if ( ( curstream = index_of_pid( stream, pid ) ) < 0 )
    {
        // Not a stream we care about
        return hb_buffer_list_clear(&list);
    }


    // Get error
    int errorbit = (pkt[1] & 0x80) != 0;
    if (errorbit)
    {
        ts_err( stream, curstream,  "packet error bit set");
        return hb_buffer_list_clear(&list);
    }

    // Get adaption header info
    int adaption = (pkt[3] & 0x30) >> 4;
    int adapt_len = 0;
    if (adaption == 0)
    {
        ts_err( stream, curstream,  "adaptation code 0");
        return hb_buffer_list_clear(&list);
    }
    else if (adaption == 0x2)
        adapt_len = 184;
    else if (adaption == 0x3)
    {
        adapt_len = pkt[4] + 1;
        if (adapt_len > 184)
        {
            ts_err( stream, curstream,  "invalid adapt len %d", adapt_len);
            return hb_buffer_list_clear(&list);
        }
    }

    if (adapt_len > 0)
    {
        if (pkt[5] & 0x40)
        {
            // found a random access point
        }
        // if there's an adaptation header & PCR_flag is set
        // get the PCR (Program Clock Reference)
        //
        // JAS: I have a badly mastered BD that does adaptation field
        // stuffing incorrectly which results in invalid PCRs.  Test
        // for all 0xff to guard against this.
        if (adapt_len > 7 && (pkt[5] & 0x10) != 0 &&
            !(pkt[5] == 0xff && pkt[6] == 0xff && pkt[7] == 0xff &&
              pkt[8] == 0xff && pkt[9] == 0xff && pkt[10] == 0xff))
        {
            // When we get a new pcr, we flush all data that was
            // referenced to the last pcr.  This makes it easier
            // for reader to resolve pcr discontinuities.
            buf = flush_ts_streams(stream);
            hb_buffer_list_append(&list, buf);

            int64_t pcr;
            pcr = ((uint64_t)pkt[ 6] << (33 -  8) ) |
                  ((uint64_t)pkt[ 7] << (33 - 16) ) |
                  ((uint64_t)pkt[ 8] << (33 - 24) ) |
                  ((uint64_t)pkt[ 9] << (33 - 32) ) |
                  (          pkt[10] >> 7         );
            stream->ts.found_pcr = 1;
            stream->ts_flags |= TS_HAS_PCR;
            stream->ts.pcr = pcr;
        }
    }

    // If we don't have a PCR yet but the stream has PCRs just loop
    // so we don't process anything until we have a clock reference.
    // Unfortunately the HD Home Run appears to null out the PCR so if
    // we didn't detect a PCR during scan keep going and we'll use
    // the video stream DTS for the PCR.
    if (!stream->ts.found_pcr && (stream->ts_flags & TS_HAS_PCR))
    {
        return hb_buffer_list_clear(&list);
    }

    // Get continuity
    // Continuity only increments for adaption values of 0x3 or 0x01
    // and is not checked for start packets.
    hb_ts_stream_t * ts_stream = &stream->ts.list[curstream];
    int start = (pkt[1] & 0x40) != 0;

    if ( (adaption & 0x01) != 0 )
    {
        int continuity = (pkt[3] & 0xF);
        if ( continuity == ts_stream->continuity )
        {
            // Spliced transport streams can have duplicate
            // continuity counts at the splice boundary.
            // Test to see if the packet is really a duplicate
            // by comparing packet summaries to see if they
            // match.
            uint8_t summary[8];

            summary[0] = adaption;
            summary[1] = adapt_len;
            if (adapt_len + 4 + 6 + 9 <= 188)
            {
                memcpy(&summary[2], pkt+4+adapt_len+9, 6);
            }
            else
            {
                memset(&summary[2], 0, 6);
            }
            if ( memcmp( summary, ts_stream->pkt_summary, 8 ) == 0 )
            {
                // we got a duplicate packet (usually used to introduce
                // a PCR when one is needed). The only thing that can
                // change in the dup is the PCR which we grabbed above
                // so ignore the rest.
                return hb_buffer_list_clear(&list);
            }
        }
        if ( !start && (ts_stream->continuity != -1) &&
             !ts_stream->skipbad &&
             (continuity != ( (ts_stream->continuity + 1) & 0xf ) ) )
        {
            if (continuity == ts_stream->continuity)
            {
                // Duplicate packet as defined by ITU-T Rec. H.222
                // Drop the packet.
                return hb_buffer_list_clear(&list);
            }
            ts_warn( stream, "continuity error: got %d expected %d",
                    (int)continuity, (ts_stream->continuity + 1) & 0xf );
            ts_stream->continuity = continuity;
        }
        ts_stream->continuity = continuity;

        // Save a summary of this packet for later duplicate
        // testing.  The summary includes some header information
        // and payload bytes.  Should be enough to detect
        // non-duplicates.
        ts_stream->pkt_summary[0] = adaption;
        ts_stream->pkt_summary[1] = adapt_len;
        if (adapt_len + 4 + 6 + 9 <= 188)
        {
            memcpy(&ts_stream->pkt_summary[2],
                    pkt+4+adapt_len+9, 6);
        }
        else
        {
            memset(&ts_stream->pkt_summary[2], 0, 6);
        }
    }

    if (ts_stream_kind( stream, curstream ) == P)
    {
        // This is a stream that only contains PCRs.  No need to process
        // the remainder of the packet.
        //
        // I ran across a poorly mastered BD that does not properly pad
        // the adaptation field and causes parsing errors below if we
        // do not exit early here.
        return hb_buffer_list_clear(&list);
    }

    /* If we get here the packet is valid - process its data */
    if (start)
    {
        // Found the start of a new PES packet.
        // If we have previous packet data on this stream,
        // output the elementary stream data for that packet.
        if (ts_stream->buf->size > 0)
        {
            // we have to ship the old packet before updating the pcr
            // since the packet we've been accumulating is referenced
            // to the old pcr.
            buf = generate_output_data(stream, curstream);
            hb_buffer_list_append(&list, buf);
        }
        ts_stream->pes_info_valid = 0;
        ts_stream->packet_len = 0;

        // PES must begin with an mpeg start code
        const uint8_t *pes = pkt + adapt_len + 4;
        if (pes[0] != 0x00 || pes[1] != 0x00 || pes[2] != 0x01)
        {
            ts_err( stream, curstream, "missing start code" );
            ts_stream->skipbad = 1;
            return hb_buffer_list_clear(&list);
        }

        // If we were skipping a bad packet, start fresh on this new PES packet
        ts_stream->skipbad = 0;

        if (curstream == video_index)
        {
            ++stream->frames;

            // if we don't have a pcr yet use the dts from this frame
            // to attempt to detect discontinuities
            if (!stream->ts.found_pcr)
            {
                // PES must begin with an mpeg start code & contain
                // a DTS or PTS.
                if (stream->ts.last_timestamp < 0 && (pes[7] >> 6) == 0)
                {
                    return hb_buffer_list_clear(&list);
                }
                if ((pes[7] >> 6) != 0)
                {
                    // if we have a dts use it otherwise use the pts
                    // We simulate a psuedo-PCR here by sampling a timestamp
                    // about every 600ms.
                    int64_t timestamp;
                    timestamp = pes_timestamp(pes + (pes[7] & 0x40 ? 14 : 9));
                    if (stream->ts.last_timestamp < 0 ||
                        timestamp - stream->ts.last_timestamp > 90 * 600 ||
                        stream->ts.last_timestamp - timestamp > 90 * 600)
                    {
                        stream->ts.pcr = timestamp;
                    }
                    stream->ts.last_timestamp = timestamp;
                }
            }
        }
    }

    // Add the payload for this packet to the current buffer
    hb_ts_stream_append_pkt(stream, curstream, pkt + 4 + adapt_len,
                            184 - adapt_len);
    if (stream->chapter > 0 &&
        stream->pes.list[ts_stream->pes_list].stream_kind == V)
    {
        ts_stream->buf->s.new_chap = stream->chapter;
        stream->chapter = 0;
    }

    if (!ts_stream->pes_info_valid && ts_stream->buf->size >= 19)
    {
        if (hb_parse_ps(stream, ts_stream->buf->data, ts_stream->buf->size,
                        &ts_stream->pes_info))
        {
            ts_stream->pes_info_valid = 1;
            ts_stream->packet_offset = ts_stream->pes_info.header_len;
        }
    }

    // see if we've hit the end of this PES packet
    if (ts_stream->pes_info_valid &&
        ts_stream->pes_info.packet_len > 0 &&
        ts_stream->packet_len >= ts_stream->pes_info.packet_len + 6)
    {
        buf = generate_output_data(stream, curstream);
        hb_buffer_list_append(&list, buf);
    }
    return hb_buffer_list_clear(&list);
}