#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_6__ {int flv_size; int flv_off; int flv_data; } ;
typedef  TYPE_2__ RTMPContext ;

/* Variables and functions */
 int get_packet (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int rtmp_read(URLContext *s, uint8_t *buf, int size)
{
    RTMPContext *rt = s->priv_data;
    int orig_size = size;
    int ret;

    while (size > 0) {
        int data_left = rt->flv_size - rt->flv_off;

        if (data_left >= size) {
            memcpy(buf, rt->flv_data + rt->flv_off, size);
            rt->flv_off += size;
            return orig_size;
        }
        if (data_left > 0) {
            memcpy(buf, rt->flv_data + rt->flv_off, data_left);
            buf  += data_left;
            size -= data_left;
            rt->flv_off = rt->flv_size;
            return data_left;
        }
        if ((ret = get_packet(s, 0)) < 0)
           return ret;
    }
    return orig_size;
}