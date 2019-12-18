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
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  libsmbc_close (TYPE_1__*) ; 
 int libsmbc_connect (TYPE_1__*) ; 
 int /*<<< orphan*/  smbc_opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int libsmbc_open_dir(URLContext *h)
{
    LIBSMBContext *libsmbc = h->priv_data;
    int ret;

    if ((ret = libsmbc_connect(h)) < 0)
        goto fail;

    if ((libsmbc->dh = smbc_opendir(h->filename)) < 0) {
        ret = AVERROR(errno);
        av_log(h, AV_LOG_ERROR, "Error opening dir: %s\n", strerror(errno));
        goto fail;
    }

    return 0;

  fail:
    libsmbc_close(h);
    return ret;
}