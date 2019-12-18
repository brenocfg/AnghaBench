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
typedef  int /*<<< orphan*/  yes ;
typedef  int /*<<< orphan*/  rcvlatency ;
typedef  int /*<<< orphan*/  peerlatency ;
typedef  int /*<<< orphan*/  latency ;
typedef  int /*<<< orphan*/  connect_timeout ;
struct TYPE_5__ {int flags; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int latency; int rcvlatency; int peerlatency; int connect_timeout; scalar_t__ mode; scalar_t__ transtype; scalar_t__ maxbw; scalar_t__ pbkeylen; int* passphrase; scalar_t__ mss; scalar_t__ ffs; scalar_t__ ipttl; scalar_t__ iptos; scalar_t__ tlpktdrop; scalar_t__ nakreport; scalar_t__ sndbuf; scalar_t__ rcvbuf; scalar_t__ lossmaxttl; scalar_t__ minversion; int* streamid; int* smoother; scalar_t__ messageapi; scalar_t__ payload_size; } ;
typedef  TYPE_2__ SRTContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  SRTO_CONNTIMEO ; 
 int /*<<< orphan*/  SRTO_FC ; 
 int /*<<< orphan*/  SRTO_IPTOS ; 
 int /*<<< orphan*/  SRTO_IPTTL ; 
 int /*<<< orphan*/  SRTO_LATENCY ; 
 int /*<<< orphan*/  SRTO_LOSSMAXTTL ; 
 int /*<<< orphan*/  SRTO_MAXBW ; 
 int /*<<< orphan*/  SRTO_MESSAGEAPI ; 
 int /*<<< orphan*/  SRTO_MINVERSION ; 
 int /*<<< orphan*/  SRTO_MSS ; 
 int /*<<< orphan*/  SRTO_NAKREPORT ; 
 int /*<<< orphan*/  SRTO_PASSPHRASE ; 
 int /*<<< orphan*/  SRTO_PAYLOADSIZE ; 
 int /*<<< orphan*/  SRTO_PBKEYLEN ; 
 int /*<<< orphan*/  SRTO_PEERLATENCY ; 
 int /*<<< orphan*/  SRTO_RCVBUF ; 
 int /*<<< orphan*/  SRTO_RCVLATENCY ; 
 int /*<<< orphan*/  SRTO_RENDEZVOUS ; 
 int /*<<< orphan*/  SRTO_SENDER ; 
 int /*<<< orphan*/  SRTO_SMOOTHER ; 
 int /*<<< orphan*/  SRTO_SNDBUF ; 
 int /*<<< orphan*/  SRTO_STREAMID ; 
 int /*<<< orphan*/  SRTO_TLPKTDROP ; 
 int /*<<< orphan*/  SRTO_TRANSTYPE ; 
 scalar_t__ SRTT_INVALID ; 
 scalar_t__ SRT_MODE_RENDEZVOUS ; 
 scalar_t__ libsrt_setsockopt (TYPE_1__*,int,int /*<<< orphan*/ ,char*,int*,int) ; 
 int strlen (int*) ; 

__attribute__((used)) static int libsrt_set_options_pre(URLContext *h, int fd)
{
    SRTContext *s = h->priv_data;
    int yes = 1;
    int latency = s->latency / 1000;
    int rcvlatency = s->rcvlatency / 1000;
    int peerlatency = s->peerlatency / 1000;
    int connect_timeout = s->connect_timeout;

    if ((s->mode == SRT_MODE_RENDEZVOUS && libsrt_setsockopt(h, fd, SRTO_RENDEZVOUS, "SRTO_RENDEZVOUS", &yes, sizeof(yes)) < 0) ||
        (s->transtype != SRTT_INVALID && libsrt_setsockopt(h, fd, SRTO_TRANSTYPE, "SRTO_TRANSTYPE", &s->transtype, sizeof(s->transtype)) < 0) ||
        (s->maxbw >= 0 && libsrt_setsockopt(h, fd, SRTO_MAXBW, "SRTO_MAXBW", &s->maxbw, sizeof(s->maxbw)) < 0) ||
        (s->pbkeylen >= 0 && libsrt_setsockopt(h, fd, SRTO_PBKEYLEN, "SRTO_PBKEYLEN", &s->pbkeylen, sizeof(s->pbkeylen)) < 0) ||
        (s->passphrase && libsrt_setsockopt(h, fd, SRTO_PASSPHRASE, "SRTO_PASSPHRASE", s->passphrase, strlen(s->passphrase)) < 0) ||
        (s->mss >= 0 && libsrt_setsockopt(h, fd, SRTO_MSS, "SRTO_MMS", &s->mss, sizeof(s->mss)) < 0) ||
        (s->ffs >= 0 && libsrt_setsockopt(h, fd, SRTO_FC, "SRTO_FC", &s->ffs, sizeof(s->ffs)) < 0) ||
        (s->ipttl >= 0 && libsrt_setsockopt(h, fd, SRTO_IPTTL, "SRTO_UPTTL", &s->ipttl, sizeof(s->ipttl)) < 0) ||
        (s->iptos >= 0 && libsrt_setsockopt(h, fd, SRTO_IPTOS, "SRTO_IPTOS", &s->iptos, sizeof(s->iptos)) < 0) ||
        (s->latency >= 0 && libsrt_setsockopt(h, fd, SRTO_LATENCY, "SRTO_LATENCY", &latency, sizeof(latency)) < 0) ||
        (s->rcvlatency >= 0 && libsrt_setsockopt(h, fd, SRTO_RCVLATENCY, "SRTO_RCVLATENCY", &rcvlatency, sizeof(rcvlatency)) < 0) ||
        (s->peerlatency >= 0 && libsrt_setsockopt(h, fd, SRTO_PEERLATENCY, "SRTO_PEERLATENCY", &peerlatency, sizeof(peerlatency)) < 0) ||
        (s->tlpktdrop >= 0 && libsrt_setsockopt(h, fd, SRTO_TLPKTDROP, "SRTO_TLPKDROP", &s->tlpktdrop, sizeof(s->tlpktdrop)) < 0) ||
        (s->nakreport >= 0 && libsrt_setsockopt(h, fd, SRTO_NAKREPORT, "SRTO_NAKREPORT", &s->nakreport, sizeof(s->nakreport)) < 0) ||
        (connect_timeout >= 0 && libsrt_setsockopt(h, fd, SRTO_CONNTIMEO, "SRTO_CONNTIMEO", &connect_timeout, sizeof(connect_timeout)) <0 ) ||
        (s->sndbuf >= 0 && libsrt_setsockopt(h, fd, SRTO_SNDBUF, "SRTO_SNDBUF", &s->sndbuf, sizeof(s->sndbuf)) < 0) ||
        (s->rcvbuf >= 0 && libsrt_setsockopt(h, fd, SRTO_RCVBUF, "SRTO_RCVBUF", &s->rcvbuf, sizeof(s->rcvbuf)) < 0) ||
        (s->lossmaxttl >= 0 && libsrt_setsockopt(h, fd, SRTO_LOSSMAXTTL, "SRTO_LOSSMAXTTL", &s->lossmaxttl, sizeof(s->lossmaxttl)) < 0) ||
        (s->minversion >= 0 && libsrt_setsockopt(h, fd, SRTO_MINVERSION, "SRTO_MINVERSION", &s->minversion, sizeof(s->minversion)) < 0) ||
        (s->streamid && libsrt_setsockopt(h, fd, SRTO_STREAMID, "SRTO_STREAMID", s->streamid, strlen(s->streamid)) < 0) ||
        (s->smoother && libsrt_setsockopt(h, fd, SRTO_SMOOTHER, "SRTO_SMOOTHER", s->smoother, strlen(s->smoother)) < 0) ||
        (s->messageapi >= 0 && libsrt_setsockopt(h, fd, SRTO_MESSAGEAPI, "SRTO_MESSAGEAPI", &s->messageapi, sizeof(s->messageapi)) < 0) ||
        (s->payload_size >= 0 && libsrt_setsockopt(h, fd, SRTO_PAYLOADSIZE, "SRTO_PAYLOADSIZE", &s->payload_size, sizeof(s->payload_size)) < 0) ||
        ((h->flags & AVIO_FLAG_WRITE) && libsrt_setsockopt(h, fd, SRTO_SENDER, "SRTO_SENDER", &yes, sizeof(yes)) < 0)) {
        return AVERROR(EIO);
    }
    return 0;
}