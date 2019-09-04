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
struct TYPE_10__ {int is_streamed; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {int write_seekable; } ;
typedef  TYPE_2__ FTPContext ;

/* Variables and functions */
 int AVIO_FLAG_READ ; 
 int AVIO_FLAG_WRITE ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ftp_close (TYPE_1__*) ; 
 int ftp_connect (TYPE_1__*,char const*) ; 
 scalar_t__ ftp_file_size (TYPE_2__*) ; 
 scalar_t__ ftp_restart (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftp_open(URLContext *h, const char *url, int flags)
{
    FTPContext *s = h->priv_data;
    int err;

    ff_dlog(h, "ftp protocol open\n");

    if ((err = ftp_connect(h, url)) < 0)
        goto fail;

    if (ftp_restart(s, 0) < 0) {
        h->is_streamed = 1;
    } else {
        if (ftp_file_size(s) < 0 && flags & AVIO_FLAG_READ)
            h->is_streamed = 1;
        if (s->write_seekable != 1 && flags & AVIO_FLAG_WRITE)
            h->is_streamed = 1;
    }

    return 0;

  fail:
    av_log(h, AV_LOG_ERROR, "FTP open failed\n");
    ftp_close(h);
    return err;
}