#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  command ;
struct TYPE_13__ {char* filename; TYPE_3__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_15__ {int nb_streamid; int /*<<< orphan*/ * nb_prev_pkt; int /*<<< orphan*/ * prev_pkt; int /*<<< orphan*/  out_chunk_size; int /*<<< orphan*/  stream; int /*<<< orphan*/  state; } ;
struct TYPE_14__ {int size; int /*<<< orphan*/ * data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ RTMPPacket ;
typedef  TYPE_3__ RTMPContext ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  RTMP_PKTDATA_DEFAULT_SIZE ; 
 int /*<<< orphan*/  RTMP_PT_INVOKE ; 
 int /*<<< orphan*/  RTMP_SYSTEM_CHANNEL ; 
 int /*<<< orphan*/  STATE_RECEIVING ; 
 int /*<<< orphan*/  STATE_SENDING ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bytestream2_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int ff_amf_read_null (int /*<<< orphan*/ *) ; 
 int ff_amf_read_number (int /*<<< orphan*/ *,double*) ; 
 int ff_amf_read_string (int /*<<< orphan*/ *,char*,int,int*) ; 
 int /*<<< orphan*/  ff_amf_write_null (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ff_amf_write_number (int /*<<< orphan*/ **,double) ; 
 int /*<<< orphan*/  ff_amf_write_string (int /*<<< orphan*/ **,char*) ; 
 int ff_rtmp_packet_create (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_rtmp_packet_destroy (TYPE_2__*) ; 
 int ff_rtmp_packet_write (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 
 int write_begin (TYPE_1__*) ; 
 int write_status (TYPE_1__*,TYPE_2__*,char*,char*) ; 

__attribute__((used)) static int send_invoke_response(URLContext *s, RTMPPacket *pkt)
{
    RTMPContext *rt = s->priv_data;
    double seqnum;
    char filename[128];
    char command[64];
    int stringlen;
    char *pchar;
    const uint8_t *p = pkt->data;
    uint8_t *pp      = NULL;
    RTMPPacket spkt  = { 0 };
    GetByteContext gbc;
    int ret;

    bytestream2_init(&gbc, p, pkt->size);
    if (ff_amf_read_string(&gbc, command, sizeof(command),
                           &stringlen)) {
        av_log(s, AV_LOG_ERROR, "Error in PT_INVOKE\n");
        return AVERROR_INVALIDDATA;
    }

    ret = ff_amf_read_number(&gbc, &seqnum);
    if (ret)
        return ret;
    ret = ff_amf_read_null(&gbc);
    if (ret)
        return ret;
    if (!strcmp(command, "FCPublish") ||
        !strcmp(command, "publish")) {
        ret = ff_amf_read_string(&gbc, filename,
                                 sizeof(filename), &stringlen);
        if (ret) {
            if (ret == AVERROR(EINVAL))
                av_log(s, AV_LOG_ERROR, "Unable to parse stream name - name too long?\n");
            else
                av_log(s, AV_LOG_ERROR, "Unable to parse stream name\n");
            return ret;
        }
        // check with url
        if (s->filename) {
            pchar = strrchr(s->filename, '/');
            if (!pchar) {
                av_log(s, AV_LOG_WARNING,
                       "Unable to find / in url %s, bad format\n",
                       s->filename);
                pchar = s->filename;
            }
            pchar++;
            if (strcmp(pchar, filename))
                av_log(s, AV_LOG_WARNING, "Unexpected stream %s, expecting"
                       " %s\n", filename, pchar);
        }
        rt->state = STATE_RECEIVING;
    }

    if (!strcmp(command, "FCPublish")) {
        if ((ret = ff_rtmp_packet_create(&spkt, RTMP_SYSTEM_CHANNEL,
                                         RTMP_PT_INVOKE, 0,
                                         RTMP_PKTDATA_DEFAULT_SIZE)) < 0) {
            av_log(s, AV_LOG_ERROR, "Unable to create response packet\n");
            return ret;
        }
        pp = spkt.data;
        ff_amf_write_string(&pp, "onFCPublish");
    } else if (!strcmp(command, "publish")) {
        ret = write_begin(s);
        if (ret < 0)
            return ret;

        // Send onStatus(NetStream.Publish.Start)
        return write_status(s, pkt, "NetStream.Publish.Start",
                           filename);
    } else if (!strcmp(command, "play")) {
        ret = write_begin(s);
        if (ret < 0)
            return ret;
        rt->state = STATE_SENDING;
        return write_status(s, pkt, "NetStream.Play.Start",
                            filename);
    } else {
        if ((ret = ff_rtmp_packet_create(&spkt, RTMP_SYSTEM_CHANNEL,
                                         RTMP_PT_INVOKE, 0,
                                         RTMP_PKTDATA_DEFAULT_SIZE)) < 0) {
            av_log(s, AV_LOG_ERROR, "Unable to create response packet\n");
            return ret;
        }
        pp = spkt.data;
        ff_amf_write_string(&pp, "_result");
        ff_amf_write_number(&pp, seqnum);
        ff_amf_write_null(&pp);
        if (!strcmp(command, "createStream")) {
            rt->nb_streamid++;
            if (rt->nb_streamid == 0 || rt->nb_streamid == 2)
                rt->nb_streamid++; /* Values 0 and 2 are reserved */
            ff_amf_write_number(&pp, rt->nb_streamid);
            /* By now we don't control which streams are removed in
             * deleteStream. There is no stream creation control
             * if a client creates more than 2^32 - 2 streams. */
        }
    }
    spkt.size = pp - spkt.data;
    ret = ff_rtmp_packet_write(rt->stream, &spkt, rt->out_chunk_size,
                               &rt->prev_pkt[1], &rt->nb_prev_pkt[1]);
    ff_rtmp_packet_destroy(&spkt);
    return ret;
}