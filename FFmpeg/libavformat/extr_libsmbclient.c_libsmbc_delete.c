#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_6__ {int /*<<< orphan*/  filename; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_7__ {int fd; } ;
typedef  TYPE_2__ LIBSMBContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  O_WRONLY ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libsmbc_close (TYPE_1__*) ; 
 int libsmbc_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  smbc_close (int) ; 
 scalar_t__ smbc_fstat (int,struct stat*) ; 
 int smbc_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ smbc_rmdir (int /*<<< orphan*/ ) ; 
 scalar_t__ smbc_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libsmbc_delete(URLContext *h)
{
    LIBSMBContext *libsmbc = h->priv_data;
    int ret;
    struct stat st;

    if ((ret = libsmbc_connect(h)) < 0)
        goto cleanup;

    if ((libsmbc->fd = smbc_open(h->filename, O_WRONLY, 0666)) < 0) {
        ret = AVERROR(errno);
        goto cleanup;
    }

    if (smbc_fstat(libsmbc->fd, &st) < 0) {
        ret = AVERROR(errno);
        goto cleanup;
    }

    smbc_close(libsmbc->fd);
    libsmbc->fd = -1;

    if (S_ISDIR(st.st_mode)) {
        if (smbc_rmdir(h->filename) < 0) {
            ret = AVERROR(errno);
            goto cleanup;
        }
    } else {
        if (smbc_unlink(h->filename) < 0) {
            ret = AVERROR(errno);
            goto cleanup;
        }
    }

    ret = 0;

cleanup:
    libsmbc_close(h);
    return ret;
}