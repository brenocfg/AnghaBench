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
typedef  int /*<<< orphan*/  uint8_t ;
struct sctp_sndrcvinfo {scalar_t__ sinfo_stream; int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int flags; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {scalar_t__ max_streams; int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ SCTPContext ;

/* Variables and functions */
 int AVERROR_BUG ; 
 int AVIO_FLAG_NONBLOCK ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_RB16 (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MSG_EOR ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int ff_neterrno () ; 
 int ff_sctp_send (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,struct sctp_sndrcvinfo*,int /*<<< orphan*/ ) ; 
 int sctp_wait_fd (int /*<<< orphan*/ ,int) ; 
 int send (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sctp_write(URLContext *h, const uint8_t *buf, int size)
{
    SCTPContext *s = h->priv_data;
    int ret;

    if (!(h->flags & AVIO_FLAG_NONBLOCK)) {
        ret = sctp_wait_fd(s->fd, 1);
        if (ret < 0)
            return ret;
    }

    if (s->max_streams) {
        /*StreamId is introduced as a 2byte code into the stream*/
        struct sctp_sndrcvinfo info = { 0 };
        info.sinfo_stream           = AV_RB16(buf);
        if (info.sinfo_stream > s->max_streams) {
            av_log(h, AV_LOG_ERROR, "bad input data\n");
            return AVERROR_BUG;
        }
        ret = ff_sctp_send(s->fd, buf + 2, size - 2, &info, MSG_EOR);
    } else
        ret = send(s->fd, buf, size, MSG_NOSIGNAL);

    return ret < 0 ? ff_neterrno() : ret;
}