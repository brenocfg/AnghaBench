#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int child_count; TYPE_4__* child; } ;
typedef  TYPE_2__ TeeContext ;
struct TYPE_7__ {int /*<<< orphan*/  url_context; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 int ffurl_closep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tee_close(URLContext *h)
{
    TeeContext *c = h->priv_data;
    int i;
    int main_ret = 0;

    for (i=0; i<c->child_count; i++) {
        int ret = ffurl_closep(&c->child[i].url_context);
        if (ret < 0)
            main_ret = ret;
    }

    av_freep(&c->child);
    c->child_count = 0;
    return main_ret;
}