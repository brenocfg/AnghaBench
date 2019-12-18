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
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int filesize; int /*<<< orphan*/  file; } ;
typedef  TYPE_2__ LIBSSHContext ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
#define  AVSEEK_SIZE 131 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
#define  SEEK_CUR 130 
#define  SEEK_END 129 
#define  SEEK_SET 128 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sftp_seek64 (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sftp_tell64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64_t libssh_seek(URLContext *h, int64_t pos, int whence)
{
    LIBSSHContext *libssh = h->priv_data;
    int64_t newpos;

    if (libssh->filesize == -1 && (whence == AVSEEK_SIZE || whence == SEEK_END)) {
        av_log(h, AV_LOG_ERROR, "Error during seeking.\n");
        return AVERROR(EIO);
    }

    switch(whence) {
    case AVSEEK_SIZE:
        return libssh->filesize;
    case SEEK_SET:
        newpos = pos;
        break;
    case SEEK_CUR:
        newpos = sftp_tell64(libssh->file) + pos;
        break;
    case SEEK_END:
        newpos = libssh->filesize + pos;
        break;
    default:
        return AVERROR(EINVAL);
    }

    if (newpos < 0) {
        av_log(h, AV_LOG_ERROR, "Seeking to nagative position.\n");
        return AVERROR(EINVAL);
    }

    if (sftp_seek64(libssh->file, newpos)) {
        av_log(h, AV_LOG_ERROR, "Error during seeking.\n");
        return AVERROR(EIO);
    }

    return newpos;
}