#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AV_RB16 (int const*) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_bits_long (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_get_bits (int /*<<< orphan*/ *,int const*,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

int
ff_rdt_parse_header(const uint8_t *buf, int len,
                    int *pset_id, int *pseq_no, int *pstream_id,
                    int *pis_keyframe, uint32_t *ptimestamp)
{
    GetBitContext gb;
    int consumed = 0, set_id, seq_no, stream_id, is_keyframe,
        len_included, need_reliable;
    uint32_t timestamp;

    /* skip status packets */
    while (len >= 5 && buf[1] == 0xFF /* status packet */) {
        int pkt_len;

        if (!(buf[0] & 0x80))
            return -1; /* not followed by a data packet */

        pkt_len = AV_RB16(buf+3);
        buf += pkt_len;
        len -= pkt_len;
        consumed += pkt_len;
    }
    if (len < 16)
        return -1;
    /**
     * Layout of the header (in bits):
     * 1:  len_included
     *     Flag indicating whether this header includes a length field;
     *     this can be used to concatenate multiple RDT packets in a
     *     single UDP/TCP data frame and is used to precede RDT data
     *     by stream status packets
     * 1:  need_reliable
     *     Flag indicating whether this header includes a "reliable
     *     sequence number"; these are apparently sequence numbers of
     *     data packets alone. For data packets, this flag is always
     *     set, according to the Real documentation [1]
     * 5:  set_id
     *     ID of a set of streams of identical content, possibly with
     *     different codecs or bitrates
     * 1:  is_reliable
     *     Flag set for certain streams deemed less tolerable for packet
     *     loss
     * 16: seq_no
     *     Packet sequence number; if >=0xFF00, this is a non-data packet
     *     containing stream status info, the second byte indicates the
     *     type of status packet (see wireshark docs / source code [2])
     * if (len_included) {
     *     16: packet_len
     * } else {
     *     packet_len = remainder of UDP/TCP frame
     * }
     * 1:  is_back_to_back
     *     Back-to-Back flag; used for timing, set for one in every 10
     *     packets, according to the Real documentation [1]
     * 1:  is_slow_data
     *     Slow-data flag; currently unused, according to Real docs [1]
     * 5:  stream_id
     *     ID of the stream within this particular set of streams
     * 1:  is_no_keyframe
     *     Non-keyframe flag (unset if packet belongs to a keyframe)
     * 32: timestamp (PTS)
     * if (set_id == 0x1F) {
     *     16: set_id (extended set-of-streams ID; see set_id)
     * }
     * if (need_reliable) {
     *     16: reliable_seq_no
     *         Reliable sequence number (see need_reliable)
     * }
     * if (stream_id == 0x3F) {
     *     16: stream_id (extended stream ID; see stream_id)
     * }
     * [1] https://protocol.helixcommunity.org/files/2005/devdocs/RDT_Feature_Level_20.txt
     * [2] http://www.wireshark.org/docs/dfref/r/rdt.html and
     *     http://anonsvn.wireshark.org/viewvc/trunk/epan/dissectors/packet-rdt.c
     */
    init_get_bits(&gb, buf, len << 3);
    len_included  = get_bits1(&gb);
    need_reliable = get_bits1(&gb);
    set_id        = get_bits(&gb, 5);
    skip_bits(&gb, 1);
    seq_no        = get_bits(&gb, 16);
    if (len_included)
        skip_bits(&gb, 16);
    skip_bits(&gb, 2);
    stream_id     = get_bits(&gb, 5);
    is_keyframe   = !get_bits1(&gb);
    timestamp     = get_bits_long(&gb, 32);
    if (set_id == 0x1f)
        set_id    = get_bits(&gb, 16);
    if (need_reliable)
        skip_bits(&gb, 16);
    if (stream_id == 0x1f)
        stream_id = get_bits(&gb, 16);

    if (pset_id)      *pset_id      = set_id;
    if (pseq_no)      *pseq_no      = seq_no;
    if (pstream_id)   *pstream_id   = stream_id;
    if (pis_keyframe) *pis_keyframe = is_keyframe;
    if (ptimestamp)   *ptimestamp   = timestamp;

    return consumed + (get_bits_count(&gb) >> 3);
}