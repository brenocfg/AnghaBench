#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_10__ {int handshake_step; int is_connected_server; int /*<<< orphan*/  reply_code; TYPE_1__* hd; } ;
typedef  TYPE_2__ HTTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  EINVAL ; 
#define  FINISH 131 
#define  LOWER_PROTO 130 
#define  READ_HEADERS 129 
#define  WRITE_REPLY_HEADERS 128 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int ffurl_handshake (TYPE_1__*) ; 
 int /*<<< orphan*/  handle_http_errors (TYPE_1__*,int) ; 
 int http_read_header (TYPE_1__*,int*) ; 
 int http_write_reply (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int http_handshake(URLContext *c)
{
    int ret, err, new_location;
    HTTPContext *ch = c->priv_data;
    URLContext *cl = ch->hd;
    switch (ch->handshake_step) {
    case LOWER_PROTO:
        av_log(c, AV_LOG_TRACE, "Lower protocol\n");
        if ((ret = ffurl_handshake(cl)) > 0)
            return 2 + ret;
        if (ret < 0)
            return ret;
        ch->handshake_step = READ_HEADERS;
        ch->is_connected_server = 1;
        return 2;
    case READ_HEADERS:
        av_log(c, AV_LOG_TRACE, "Read headers\n");
        if ((err = http_read_header(c, &new_location)) < 0) {
            handle_http_errors(c, err);
            return err;
        }
        ch->handshake_step = WRITE_REPLY_HEADERS;
        return 1;
    case WRITE_REPLY_HEADERS:
        av_log(c, AV_LOG_TRACE, "Reply code: %d\n", ch->reply_code);
        if ((err = http_write_reply(c, ch->reply_code)) < 0)
            return err;
        ch->handshake_step = FINISH;
        return 1;
    case FINISH:
        return 0;
    }
    // this should never be reached.
    return AVERROR(EINVAL);
}