#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  path ;
struct TYPE_7__ {int /*<<< orphan*/  filename; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {int /*<<< orphan*/  session; int /*<<< orphan*/  sftp; int /*<<< orphan*/  dir; } ;
typedef  TYPE_2__ LIBSSHContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EIO ; 
 int MAX_URL_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libssh_close (TYPE_1__*) ; 
 int libssh_connect (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sftp_opendir (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ssh_get_error (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libssh_open_dir(URLContext *h)
{
    LIBSSHContext *libssh = h->priv_data;
    int ret;
    char path[MAX_URL_SIZE];

    if ((ret = libssh_connect(h, h->filename, path, sizeof(path))) < 0)
        goto fail;

    if (!(libssh->dir = sftp_opendir(libssh->sftp, path))) {
        av_log(libssh, AV_LOG_ERROR, "Error opening sftp dir: %s\n", ssh_get_error(libssh->session));
        ret = AVERROR(EIO);
        goto fail;
    }

    return 0;

  fail:
    libssh_close(h);
    return ret;
}