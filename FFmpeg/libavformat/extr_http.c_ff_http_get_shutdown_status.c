#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int /*<<< orphan*/  hd; } ;
typedef  TYPE_2__ HTTPContext ;

/* Variables and functions */
 int ffurl_read (int /*<<< orphan*/ ,char*,int) ; 

int ff_http_get_shutdown_status(URLContext *h)
{
    int ret = 0;
    HTTPContext *s = h->priv_data;

    /* flush the receive buffer when it is write only mode */
    char buf[1024];
    int read_ret;
    read_ret = ffurl_read(s->hd, buf, sizeof(buf));
    if (read_ret < 0) {
        ret = read_ret;
    }

    return ret;
}