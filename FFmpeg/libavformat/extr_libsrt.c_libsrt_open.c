#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {void* streamid; void* smoother; int /*<<< orphan*/  transtype; void* messageapi; void* minversion; void* lossmaxttl; void* rcvbuf; void* sndbuf; int /*<<< orphan*/  mode; void* payload_size; void* connect_timeout; void* nakreport; void* tlpktdrop; void* peerlatency; void* rcvlatency; void* latency; void* oheadbw; void* inputbw; void* iptos; void* ipttl; void* ffs; void* mss; int /*<<< orphan*/  passphrase; void* pbkeylen; void* maxbw; } ;
typedef  TYPE_2__ SRTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SRTT_FILE ; 
 int /*<<< orphan*/  SRTT_LIVE ; 
 int /*<<< orphan*/  SRT_MODE_CALLER ; 
 int /*<<< orphan*/  SRT_MODE_LISTENER ; 
 int /*<<< orphan*/  SRT_MODE_RENDEZVOUS ; 
 scalar_t__ av_find_info_tag (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  av_freep (void**) ; 
 void* av_strdup (char*) ; 
 int /*<<< orphan*/  av_strndup (char*,int /*<<< orphan*/ ) ; 
 int libsrt_setup (TYPE_1__*,char const*,int) ; 
 scalar_t__ srt_startup () ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 void* strtol (char*,int /*<<< orphan*/ *,int) ; 
 void* strtoll (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int libsrt_open(URLContext *h, const char *uri, int flags)
{
    SRTContext *s = h->priv_data;
    const char * p;
    char buf[256];
    int ret = 0;

    if (srt_startup() < 0) {
        return AVERROR_UNKNOWN;
    }

    /* SRT options (srt/srt.h) */
    p = strchr(uri, '?');
    if (p) {
        if (av_find_info_tag(buf, sizeof(buf), "maxbw", p)) {
            s->maxbw = strtoll(buf, NULL, 0);
        }
        if (av_find_info_tag(buf, sizeof(buf), "pbkeylen", p)) {
            s->pbkeylen = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "passphrase", p)) {
            s->passphrase = av_strndup(buf, strlen(buf));
        }
        if (av_find_info_tag(buf, sizeof(buf), "mss", p)) {
            s->mss = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "ffs", p)) {
            s->ffs = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "ipttl", p)) {
            s->ipttl = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "iptos", p)) {
            s->iptos = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "inputbw", p)) {
            s->inputbw = strtoll(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "oheadbw", p)) {
            s->oheadbw = strtoll(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "latency", p)) {
            s->latency = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "tsbpddelay", p)) {
            s->latency = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "rcvlatency", p)) {
            s->rcvlatency = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "peerlatency", p)) {
            s->peerlatency = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "tlpktdrop", p)) {
            s->tlpktdrop = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "nakreport", p)) {
            s->nakreport = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "connect_timeout", p)) {
            s->connect_timeout = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "payload_size", p) ||
            av_find_info_tag(buf, sizeof(buf), "pkt_size", p)) {
            s->payload_size = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "mode", p)) {
            if (!strcmp(buf, "caller")) {
                s->mode = SRT_MODE_CALLER;
            } else if (!strcmp(buf, "listener")) {
                s->mode = SRT_MODE_LISTENER;
            } else if (!strcmp(buf, "rendezvous")) {
                s->mode = SRT_MODE_RENDEZVOUS;
            } else {
                return AVERROR(EIO);
            }
        }
        if (av_find_info_tag(buf, sizeof(buf), "sndbuf", p)) {
            s->sndbuf = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "rcvbuf", p)) {
            s->rcvbuf = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "lossmaxttl", p)) {
            s->lossmaxttl = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "minversion", p)) {
            s->minversion = strtol(buf, NULL, 0);
        }
        if (av_find_info_tag(buf, sizeof(buf), "streamid", p)) {
            av_freep(&s->streamid);
            s->streamid = av_strdup(buf);
            if (!s->streamid) {
                ret = AVERROR(ENOMEM);
                goto err;
            }
        }
        if (av_find_info_tag(buf, sizeof(buf), "smoother", p)) {
            av_freep(&s->smoother);
            s->smoother = av_strdup(buf);
            if(!s->smoother) {
                ret = AVERROR(ENOMEM);
                goto err;
            }
        }
        if (av_find_info_tag(buf, sizeof(buf), "messageapi", p)) {
            s->messageapi = strtol(buf, NULL, 10);
        }
        if (av_find_info_tag(buf, sizeof(buf), "transtype", p)) {
            if (!strcmp(buf, "live")) {
                s->transtype = SRTT_LIVE;
            } else if (!strcmp(buf, "file")) {
                s->transtype = SRTT_FILE;
            } else {
                ret = AVERROR(EINVAL);
                goto err;
            }
        }
    }
    return libsrt_setup(h, uri, flags);
err:
    av_freep(&s->smoother);
    av_freep(&s->streamid);
    return ret;
}