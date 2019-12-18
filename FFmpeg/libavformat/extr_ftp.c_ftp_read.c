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
typedef  void* int64_t ;
struct TYPE_10__ {int /*<<< orphan*/  is_streamed; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {scalar_t__ state; scalar_t__ position; scalar_t__ filesize; scalar_t__ conn_data; } ;
typedef  TYPE_2__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 scalar_t__ DISCONNECTED ; 
 scalar_t__ DOWNLOADING ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ READY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ff_dlog (TYPE_1__*,char*,int) ; 
 int ffurl_read (scalar_t__,unsigned char*,int) ; 
 int ftp_abort (TYPE_1__*) ; 
 int ftp_connect_data_connection (TYPE_1__*) ; 
 int ftp_retrieve (TYPE_2__*) ; 
 int ftp_seek (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftp_read(URLContext *h, unsigned char *buf, int size)
{
    FTPContext *s = h->priv_data;
    int read, err, retry_done = 0;

    ff_dlog(h, "ftp protocol read %d bytes\n", size);
  retry:
    if (s->state == DISCONNECTED) {
        /* optimization */
        if (s->position >= s->filesize)
            return AVERROR_EOF;
        if ((err = ftp_connect_data_connection(h)) < 0)
            return err;
    }
    if (s->state == READY) {
        if (s->position >= s->filesize)
            return AVERROR_EOF;
        if ((err = ftp_retrieve(s)) < 0)
            return err;
    }
    if (s->conn_data && s->state == DOWNLOADING) {
        read = ffurl_read(s->conn_data, buf, size);
        if (read >= 0) {
            s->position += read;
            if (s->position >= s->filesize) {
                /* server will terminate, but keep current position to avoid madness */
                /* save position to restart from it */
                int64_t pos = s->position;
                if (ftp_abort(h) < 0) {
                    s->position = pos;
                    return AVERROR(EIO);
                }
                s->position = pos;
            }
        }
        if (read <= 0 && s->position < s->filesize && !h->is_streamed) {
            /* Server closed connection. Probably due to inactivity */
            int64_t pos = s->position;
            av_log(h, AV_LOG_INFO, "Reconnect to FTP server.\n");
            if ((err = ftp_abort(h)) < 0)
                return err;
            if ((err = ftp_seek(h, pos, SEEK_SET)) < 0) {
                av_log(h, AV_LOG_ERROR, "Position cannot be restored.\n");
                return err;
            }
            if (!retry_done) {
                retry_done = 1;
                goto retry;
            }
        }
        return read;
    }

    av_log(h, AV_LOG_DEBUG, "FTP read failed\n");
    return AVERROR(EIO);
}