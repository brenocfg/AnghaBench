#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  include_sources ;
typedef  int /*<<< orphan*/  hostname ;
typedef  int /*<<< orphan*/  exclude_sources ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_14__ {int is_streamed; int /*<<< orphan*/  max_packet_size; int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_16__ {int /*<<< orphan*/  max_packet_size; } ;
struct TYPE_15__ {int rtcp_port; scalar_t__ ttl; int local_rtpport; int local_rtcpport; char* sources; char* block; char* fec_options_str; TYPE_4__* fec_hd; TYPE_4__* rtcp_hd; TYPE_4__* rtp_hd; void* rtcp_fd; void* rtp_fd; int /*<<< orphan*/  filters; void* dscp; void* write_to_source; void* connect; void* pkt_size; } ;
typedef  TYPE_2__ RTPContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_dict_parse_string (int /*<<< orphan*/ **,char const*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ av_find_info_tag (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_get_token (char const**,char*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int*,char*,int,char const*) ; 
 int /*<<< orphan*/  build_udp_url (TYPE_2__*,char*,int,char*,int,int,char*,char*) ; 
 int /*<<< orphan*/  ff_ip_parse_blocks (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_ip_parse_sources (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int ff_udp_get_local_port (TYPE_4__*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffurl_close (TYPE_4__*) ; 
 int /*<<< orphan*/  ffurl_closep (TYPE_4__**) ; 
 void* ffurl_get_file_handle (TYPE_4__*) ; 
 scalar_t__ ffurl_open_whitelist (TYPE_4__**,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int rtp_open(URLContext *h, const char *uri, int flags)
{
    RTPContext *s = h->priv_data;
    AVDictionary *fec_opts = NULL;
    int rtp_port;
    char hostname[256], include_sources[1024] = "", exclude_sources[1024] = "";
    char *sources = include_sources, *block = exclude_sources;
    char *fec_protocol = NULL;
    char buf[1024];
    char path[1024];
    const char *p;
    int i, max_retry_count = 3;
    int rtcpflags;

    av_url_split(NULL, 0, NULL, 0, hostname, sizeof(hostname), &rtp_port,
                 path, sizeof(path), uri);
    /* extract parameters */
    if (s->rtcp_port < 0)
        s->rtcp_port = rtp_port + 1;

    p = strchr(uri, '?');
    if (p) {
        if (av_find_info_tag(buf, sizeof(buf), "ttl", p)) {
            s->ttl = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "rtcpport", p)) {
            s->rtcp_port = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "localport", p)) {
            s->local_rtpport = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "localrtpport", p)) {
            s->local_rtpport = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "localrtcpport", p)) {
            s->local_rtcpport = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "pkt_size", p)) {
            s->pkt_size = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "connect", p)) {
            s->connect = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "write_to_source", p)) {
            s->write_to_source = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "dscp", p)) {
            s->dscp = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "sources", p)) {
            av_strlcpy(include_sources, buf, sizeof(include_sources));
            ff_ip_parse_sources(h, buf, &s->filters);
        } else {
            ff_ip_parse_sources(h, s->sources, &s->filters);
            sources = s->sources;
        }
        if (av_find_info_tag(buf, sizeof(buf), "block", p)) {
            av_strlcpy(exclude_sources, buf, sizeof(exclude_sources));
            ff_ip_parse_blocks(h, buf, &s->filters);
        } else {
            ff_ip_parse_blocks(h, s->block, &s->filters);
            block = s->block;
        }
    }

    if (s->fec_options_str) {
        p = s->fec_options_str;

        if (!(fec_protocol = av_get_token(&p, "="))) {
            av_log(h, AV_LOG_ERROR, "Failed to parse the FEC protocol value\n");
            goto fail;
        }
        if (strcmp(fec_protocol, "prompeg")) {
            av_log(h, AV_LOG_ERROR, "Unsupported FEC protocol %s\n", fec_protocol);
            goto fail;
        }

        p = s->fec_options_str + strlen(fec_protocol);
        while (*p && *p == '=') p++;

        if (av_dict_parse_string(&fec_opts, p, "=", ":", 0) < 0) {
            av_log(h, AV_LOG_ERROR, "Failed to parse the FEC options\n");
            goto fail;
        }
        if (s->ttl > 0) {
            snprintf(buf, sizeof (buf), "%d", s->ttl);
            av_dict_set(&fec_opts, "ttl", buf, 0);
        }
    }

    for (i = 0; i < max_retry_count; i++) {
        build_udp_url(s, buf, sizeof(buf),
                      hostname, rtp_port, s->local_rtpport,
                      sources, block);
        if (ffurl_open_whitelist(&s->rtp_hd, buf, flags, &h->interrupt_callback,
                                 NULL, h->protocol_whitelist, h->protocol_blacklist, h) < 0)
            goto fail;
        s->local_rtpport = ff_udp_get_local_port(s->rtp_hd);
        if(s->local_rtpport == 65535) {
            s->local_rtpport = -1;
            continue;
        }
        rtcpflags = flags | AVIO_FLAG_WRITE;
        if (s->local_rtcpport < 0) {
            s->local_rtcpport = s->local_rtpport + 1;
            build_udp_url(s, buf, sizeof(buf),
                          hostname, s->rtcp_port, s->local_rtcpport,
                          sources, block);
            if (ffurl_open_whitelist(&s->rtcp_hd, buf, rtcpflags,
                                     &h->interrupt_callback, NULL,
                                     h->protocol_whitelist, h->protocol_blacklist, h) < 0) {
                s->local_rtpport = s->local_rtcpport = -1;
                continue;
            }
            break;
        }
        build_udp_url(s, buf, sizeof(buf),
                      hostname, s->rtcp_port, s->local_rtcpport,
                      sources, block);
        if (ffurl_open_whitelist(&s->rtcp_hd, buf, rtcpflags, &h->interrupt_callback,
                                 NULL, h->protocol_whitelist, h->protocol_blacklist, h) < 0)
            goto fail;
        break;
    }

    s->fec_hd = NULL;
    if (fec_protocol) {
        ff_url_join(buf, sizeof(buf), fec_protocol, NULL, hostname, rtp_port, NULL);
        if (ffurl_open_whitelist(&s->fec_hd, buf, flags, &h->interrupt_callback,
                             &fec_opts, h->protocol_whitelist, h->protocol_blacklist, h) < 0)
            goto fail;
    }

    /* just to ease handle access. XXX: need to suppress direct handle
       access */
    s->rtp_fd = ffurl_get_file_handle(s->rtp_hd);
    s->rtcp_fd = ffurl_get_file_handle(s->rtcp_hd);

    h->max_packet_size = s->rtp_hd->max_packet_size;
    h->is_streamed = 1;

    av_free(fec_protocol);
    av_dict_free(&fec_opts);

    return 0;

 fail:
    if (s->rtp_hd)
        ffurl_close(s->rtp_hd);
    if (s->rtcp_hd)
        ffurl_close(s->rtcp_hd);
    ffurl_closep(&s->fec_hd);
    av_free(fec_protocol);
    av_dict_free(&fec_opts);
    return AVERROR(EIO);
}