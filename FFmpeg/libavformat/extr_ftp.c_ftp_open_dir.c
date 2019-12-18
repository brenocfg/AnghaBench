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
struct TYPE_8__ {int /*<<< orphan*/  filename; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_9__ {scalar_t__ state; scalar_t__ conn_data; scalar_t__ conn_control; scalar_t__* dir_buffer; } ;
typedef  TYPE_2__ FTPContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIR_BUFFER_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ LISTING_DIR ; 
 scalar_t__* av_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffurl_closep (scalar_t__*) ; 
 int ftp_connect (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ftp_connect_data_connection (TYPE_1__*) ; 
 int ftp_list (TYPE_2__*) ; 
 int ftp_set_dir (TYPE_2__*) ; 

__attribute__((used)) static int ftp_open_dir(URLContext *h)
{
    FTPContext *s = h->priv_data;
    int ret;

    if ((ret = ftp_connect(h, h->filename)) < 0)
        goto fail;
    if ((ret = ftp_set_dir(s)) < 0)
        goto fail;
    if ((ret = ftp_connect_data_connection(h)) < 0)
        goto fail;
    if ((ret = ftp_list(s)) < 0)
        goto fail;
    s->dir_buffer = av_malloc(DIR_BUFFER_SIZE);
    if (!s->dir_buffer) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }
    s->dir_buffer[0] = 0;
    if (s->conn_data && s->state == LISTING_DIR)
        return 0;
  fail:
    ffurl_closep(&s->conn_control);
    ffurl_closep(&s->conn_data);
    return ret;
}