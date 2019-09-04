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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_5__ {int out_size; int out_capacity; scalar_t__ out_data; } ;
typedef  TYPE_2__ RTMP_HTTPContext ;

/* Variables and functions */
 int av_reallocp (scalar_t__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int rtmp_http_write(URLContext *h, const uint8_t *buf, int size)
{
    RTMP_HTTPContext *rt = h->priv_data;

    if (rt->out_size + size > rt->out_capacity) {
        int err;
        rt->out_capacity = (rt->out_size + size) * 2;
        if ((err = av_reallocp(&rt->out_data, rt->out_capacity)) < 0) {
            rt->out_size = 0;
            rt->out_capacity = 0;
            return err;
        }
    }

    memcpy(rt->out_data + rt->out_size, buf, size);
    rt->out_size += size;

    return size;
}