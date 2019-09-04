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
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_2__ LIBSMBContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int smbc_read (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libsmbc_read(URLContext *h, unsigned char *buf, int size)
{
    LIBSMBContext *libsmbc = h->priv_data;
    int bytes_read;

    if ((bytes_read = smbc_read(libsmbc->fd, buf, size)) < 0) {
        int ret = AVERROR(errno);
        av_log(h, AV_LOG_ERROR, "Read error: %s\n", strerror(errno));
        return ret;
    }

    return bytes_read ? bytes_read : AVERROR_EOF;
}