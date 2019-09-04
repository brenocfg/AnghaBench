#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* sftp_attributes ;
typedef  int /*<<< orphan*/  path ;
struct TYPE_10__ {int /*<<< orphan*/  filename; TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_11__ {int /*<<< orphan*/  sftp; } ;
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_3__ LIBSSHContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int MAX_URL_SIZE ; 
 scalar_t__ SSH_FILEXFER_TYPE_DIRECTORY ; 
 int /*<<< orphan*/  libssh_close (TYPE_2__*) ; 
 int libssh_connect (TYPE_2__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sftp_attributes_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sftp_get_error (int /*<<< orphan*/ ) ; 
 scalar_t__ sftp_rmdir (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* sftp_stat (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sftp_unlink (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int libssh_delete(URLContext *h)
{
    int ret;
    LIBSSHContext *libssh = h->priv_data;
    sftp_attributes attr = NULL;
    char path[MAX_URL_SIZE];

    if ((ret = libssh_connect(h, h->filename, path, sizeof(path))) < 0)
        goto cleanup;

    if (!(attr = sftp_stat(libssh->sftp, path))) {
        ret = AVERROR(sftp_get_error(libssh->sftp));
        goto cleanup;
    }

    if (attr->type == SSH_FILEXFER_TYPE_DIRECTORY) {
        if (sftp_rmdir(libssh->sftp, path) < 0) {
            ret = AVERROR(sftp_get_error(libssh->sftp));
            goto cleanup;
        }
    } else {
        if (sftp_unlink(libssh->sftp, path) < 0) {
            ret = AVERROR(sftp_get_error(libssh->sftp));
            goto cleanup;
        }
    }

    ret = 0;

cleanup:
    if (attr)
        sftp_attributes_free(attr);
    libssh_close(h);
    return ret;
}