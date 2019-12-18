#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* priv_data; } ;
typedef  TYPE_2__ URLContext ;
struct TYPE_7__ {int child_count; TYPE_1__* child; } ;
typedef  TYPE_3__ TeeContext ;
struct TYPE_5__ {int /*<<< orphan*/  url_context; } ;

/* Variables and functions */
 int ffurl_write (int /*<<< orphan*/ ,unsigned char const*,int) ; 

__attribute__((used)) static int tee_write(URLContext *h, const unsigned char *buf, int size)
{
    TeeContext *c = h->priv_data;
    int i;
    int main_ret = size;

    for (i=0; i<c->child_count; i++) {
        int ret = ffurl_write(c->child[i].url_context, buf, size);
        if (ret < 0)
            main_ret = ret;
    }
    return main_ret;
}