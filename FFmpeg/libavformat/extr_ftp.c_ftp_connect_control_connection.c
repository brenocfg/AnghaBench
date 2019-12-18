#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_10__ {int flags; int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {int rw_timeout; int /*<<< orphan*/  conn_control; int /*<<< orphan*/  server_control_port; int /*<<< orphan*/  hostname; } ;
typedef  TYPE_2__ FTPContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVIO_FLAG_READ_WRITE ; 
 int AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int CONTROL_BUFFER_SIZE ; 
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_stristr (char*,char*) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ftp_auth (TYPE_2__*) ; 
 int /*<<< orphan*/  ftp_features (TYPE_2__*) ; 
 int ftp_status (TYPE_2__*,char**,int const*) ; 
 int ftp_type (TYPE_2__*) ; 

__attribute__((used)) static int ftp_connect_control_connection(URLContext *h)
{
    char buf[CONTROL_BUFFER_SIZE], *response = NULL;
    int err;
    AVDictionary *opts = NULL;
    FTPContext *s = h->priv_data;
    static const int connect_codes[] = {220, 0};

    if (!s->conn_control) {
        ff_url_join(buf, sizeof(buf), "tcp", NULL,
                    s->hostname, s->server_control_port, NULL);
        if (s->rw_timeout != -1) {
            av_dict_set_int(&opts, "timeout", s->rw_timeout, 0);
        } /* if option is not given, don't pass it and let tcp use its own default */
        err = ffurl_open_whitelist(&s->conn_control, buf, AVIO_FLAG_READ_WRITE,
                                   &h->interrupt_callback, &opts,
                                   h->protocol_whitelist, h->protocol_blacklist, h);
        av_dict_free(&opts);
        if (err < 0) {
            av_log(h, AV_LOG_ERROR, "Cannot open control connection\n");
            return err;
        }

        /* check if server is ready */
        if (ftp_status(s, ((h->flags & AVIO_FLAG_WRITE) ? &response : NULL), connect_codes) != 220) {
            av_log(h, AV_LOG_ERROR, "FTP server not ready for new users\n");
            return AVERROR(EACCES);
        }

        if ((h->flags & AVIO_FLAG_WRITE) && av_stristr(response, "pure-ftpd")) {
            av_log(h, AV_LOG_WARNING, "Pure-FTPd server is used as an output protocol. It is known issue this implementation may produce incorrect content and it cannot be fixed at this moment.");
        }
        av_free(response);

        if ((err = ftp_auth(s)) < 0) {
            av_log(h, AV_LOG_ERROR, "FTP authentication failed\n");
            return err;
        }

        if ((err = ftp_type(s)) < 0) {
            av_log(h, AV_LOG_ERROR, "Set content type failed\n");
            return err;
        }

        ftp_features(s);
    }
    return 0;
}