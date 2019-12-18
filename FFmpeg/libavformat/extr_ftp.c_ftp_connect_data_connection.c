#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {int /*<<< orphan*/  protocol_blacklist; int /*<<< orphan*/  protocol_whitelist; int /*<<< orphan*/  interrupt_callback; int /*<<< orphan*/  flags; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {int rw_timeout; int /*<<< orphan*/  state; scalar_t__ position; int /*<<< orphan*/  conn_data; int /*<<< orphan*/  server_data_port; int /*<<< orphan*/  hostname; } ;
typedef  TYPE_2__ FTPContext ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int CONTROL_BUFFER_SIZE ; 
 int /*<<< orphan*/  READY ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ **,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_url_join (char*,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ffurl_open_whitelist (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int ftp_passive_mode (TYPE_2__*) ; 
 scalar_t__ ftp_passive_mode_epsv (TYPE_2__*) ; 
 int ftp_restart (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static int ftp_connect_data_connection(URLContext *h)
{
    int err;
    char buf[CONTROL_BUFFER_SIZE];
    AVDictionary *opts = NULL;
    FTPContext *s = h->priv_data;

    if (!s->conn_data) {
        /* Enter passive mode */
        if (ftp_passive_mode_epsv(s) < 0) {
            /* Use PASV as fallback */
            if ((err = ftp_passive_mode(s)) < 0)
                return err;
        }
        /* Open data connection */
        ff_url_join(buf, sizeof(buf), "tcp", NULL, s->hostname, s->server_data_port, NULL);
        if (s->rw_timeout != -1) {
            av_dict_set_int(&opts, "timeout", s->rw_timeout, 0);
        } /* if option is not given, don't pass it and let tcp use its own default */
        err = ffurl_open_whitelist(&s->conn_data, buf, h->flags,
                                   &h->interrupt_callback, &opts,
                                   h->protocol_whitelist, h->protocol_blacklist, h);
        av_dict_free(&opts);
        if (err < 0)
            return err;

        if (s->position)
            if ((err = ftp_restart(s, s->position)) < 0)
                return err;
    }
    s->state = READY;
    return 0;
}