#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  url ;
struct TYPE_14__ {scalar_t__ start_time_realtime; char* url; int nb_streams; TYPE_2__* priv_data; } ;
struct TYPE_13__ {scalar_t__ status_code; } ;
struct TYPE_12__ {int /*<<< orphan*/  control_uri; int /*<<< orphan*/  nb_rtsp_streams; int /*<<< orphan*/  rtsp_streams; } ;
struct TYPE_11__ {int stream_index; int /*<<< orphan*/  control_url; } ;
typedef  TYPE_1__ RTSPStream ;
typedef  TYPE_2__ RTSPState ;
typedef  TYPE_3__ RTSPMessageHeader ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ RTSP_STATUS_OK ; 
 int SDP_MAX_SIZE ; 
 int /*<<< orphan*/  av_free (char*) ; 
 scalar_t__ av_gettime () ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,char*) ; 
 void* av_mallocz (int) ; 
 scalar_t__ av_sdp_create (TYPE_4__**,int,char*,int) ; 
 int /*<<< orphan*/  av_strlcatf (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  av_strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int ff_rtsp_averror (scalar_t__,int) ; 
 int /*<<< orphan*/  ff_rtsp_send_cmd_with_content (TYPE_4__*,char*,int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int ff_rtsp_setup_output_streams(AVFormatContext *s, const char *addr)
{
    RTSPState *rt = s->priv_data;
    RTSPMessageHeader reply1, *reply = &reply1;
    int i;
    char *sdp;
    AVFormatContext sdp_ctx, *ctx_array[1];
    char url[1024];

    if (s->start_time_realtime == 0  ||  s->start_time_realtime == AV_NOPTS_VALUE)
        s->start_time_realtime = av_gettime();

    /* Announce the stream */
    sdp = av_mallocz(SDP_MAX_SIZE);
    if (!sdp)
        return AVERROR(ENOMEM);
    /* We create the SDP based on the RTSP AVFormatContext where we
     * aren't allowed to change the filename field. (We create the SDP
     * based on the RTSP context since the contexts for the RTP streams
     * don't exist yet.) In order to specify a custom URL with the actual
     * peer IP instead of the originally specified hostname, we create
     * a temporary copy of the AVFormatContext, where the custom URL is set.
     *
     * FIXME: Create the SDP without copying the AVFormatContext.
     * This either requires setting up the RTP stream AVFormatContexts
     * already here (complicating things immensely) or getting a more
     * flexible SDP creation interface.
     */
    sdp_ctx = *s;
    sdp_ctx.url = url;
    ff_url_join(url, sizeof(url),
                "rtsp", NULL, addr, -1, NULL);
    ctx_array[0] = &sdp_ctx;
    if (av_sdp_create(ctx_array, 1, sdp, SDP_MAX_SIZE)) {
        av_free(sdp);
        return AVERROR_INVALIDDATA;
    }
    av_log(s, AV_LOG_VERBOSE, "SDP:\n%s\n", sdp);
    ff_rtsp_send_cmd_with_content(s, "ANNOUNCE", rt->control_uri,
                                  "Content-Type: application/sdp\r\n",
                                  reply, NULL, sdp, strlen(sdp));
    av_free(sdp);
    if (reply->status_code != RTSP_STATUS_OK)
        return ff_rtsp_averror(reply->status_code, AVERROR_INVALIDDATA);

    /* Set up the RTSPStreams for each AVStream */
    for (i = 0; i < s->nb_streams; i++) {
        RTSPStream *rtsp_st;

        rtsp_st = av_mallocz(sizeof(RTSPStream));
        if (!rtsp_st)
            return AVERROR(ENOMEM);
        dynarray_add(&rt->rtsp_streams, &rt->nb_rtsp_streams, rtsp_st);

        rtsp_st->stream_index = i;

        av_strlcpy(rtsp_st->control_url, rt->control_uri, sizeof(rtsp_st->control_url));
        /* Note, this must match the relative uri set in the sdp content */
        av_strlcatf(rtsp_st->control_url, sizeof(rtsp_st->control_url),
                    "/streamid=%d", i);
    }

    return 0;
}