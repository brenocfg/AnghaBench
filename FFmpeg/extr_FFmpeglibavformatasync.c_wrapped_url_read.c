#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_4__ {int inner_io_error; int /*<<< orphan*/  inner; } ;
typedef  TYPE_2__ Context ;

/* Variables and functions */
 int ffurl_read (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int wrapped_url_read(void *src, void *dst, int size)
{
    URLContext *h   = src;
    Context    *c   = h->priv_data;
    int         ret;

    ret = ffurl_read(c->inner, dst, size);
    c->inner_io_error = ret < 0 ? ret : 0;

    return ret;
}