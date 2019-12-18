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
struct TYPE_7__ {int /*<<< orphan*/  filename; TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_8__ {int /*<<< orphan*/  dh; } ;
typedef  TYPE_2__ LIBSMBContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libsmbc_close (TYPE_1__*) ; 
 int libsmbc_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  smbc_rename (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libsmbc_move(URLContext *h_src, URLContext *h_dst)
{
    LIBSMBContext *libsmbc = h_src->priv_data;
    int ret;

    if ((ret = libsmbc_connect(h_src)) < 0)
        goto cleanup;

    if ((libsmbc->dh = smbc_rename(h_src->filename, h_dst->filename)) < 0) {
        ret = AVERROR(errno);
        goto cleanup;
    }

    ret = 0;

cleanup:
    libsmbc_close(h_src);
    return ret;
}