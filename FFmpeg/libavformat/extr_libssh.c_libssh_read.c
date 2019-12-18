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
struct TYPE_6__ {int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ LIBSSHContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int sftp_read (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int libssh_read(URLContext *h, unsigned char *buf, int size)
{
    LIBSSHContext *libssh = h->priv_data;
    int bytes_read;

    if ((bytes_read = sftp_read(libssh->file, buf, size)) < 0) {
        av_log(libssh, AV_LOG_ERROR, "Read error.\n");
        return AVERROR(EIO);
    }
    return bytes_read ? bytes_read : AVERROR_EOF;
}