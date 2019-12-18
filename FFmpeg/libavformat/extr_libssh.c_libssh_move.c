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
typedef  int /*<<< orphan*/  path_src ;
typedef  int /*<<< orphan*/  path_dst ;
typedef  int /*<<< orphan*/  hostname_src ;
typedef  int /*<<< orphan*/  hostname_dst ;
typedef  int /*<<< orphan*/  credentials_src ;
typedef  int /*<<< orphan*/  credentials_dst ;
struct TYPE_7__ {int /*<<< orphan*/  filename; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {int /*<<< orphan*/  sftp; } ;
typedef  TYPE_2__ LIBSSHContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int MAX_URL_SIZE ; 
 int /*<<< orphan*/  av_url_split (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,char*,int,int*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libssh_close (TYPE_1__*) ; 
 int libssh_connect (TYPE_1__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sftp_get_error (int /*<<< orphan*/ ) ; 
 scalar_t__ sftp_rename (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int libssh_move(URLContext *h_src, URLContext *h_dst)
{
    int ret;
    LIBSSHContext *libssh = h_src->priv_data;
    char path_src[MAX_URL_SIZE], path_dst[MAX_URL_SIZE];
    char hostname_src[1024], hostname_dst[1024];
    char credentials_src[1024], credentials_dst[1024];
    int port_src = 22, port_dst = 22;

    av_url_split(NULL, 0,
                 credentials_src, sizeof(credentials_src),
                 hostname_src, sizeof(hostname_src),
                 &port_src,
                 path_src, sizeof(path_src),
                 h_src->filename);

    av_url_split(NULL, 0,
                 credentials_dst, sizeof(credentials_dst),
                 hostname_dst, sizeof(hostname_dst),
                 &port_dst,
                 path_dst, sizeof(path_dst),
                 h_dst->filename);

    if (strcmp(credentials_src, credentials_dst) ||
            strcmp(hostname_src, hostname_dst) ||
            port_src != port_dst) {
        return AVERROR(EINVAL);
    }

    if ((ret = libssh_connect(h_src, h_src->filename, path_src, sizeof(path_src))) < 0)
        goto cleanup;

    if (sftp_rename(libssh->sftp, path_src, path_dst) < 0) {
        ret = AVERROR(sftp_get_error(libssh->sftp));
        goto cleanup;
    }

    ret = 0;

cleanup:
    libssh_close(h_src);
    return ret;
}