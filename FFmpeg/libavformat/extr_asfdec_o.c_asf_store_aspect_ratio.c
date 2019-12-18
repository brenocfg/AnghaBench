#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  void* uint64_t ;
struct TYPE_9__ {TYPE_2__* asf_sd; } ;
struct TYPE_8__ {int /*<<< orphan*/ * pb; TYPE_4__* priv_data; } ;
struct TYPE_6__ {void* den; void* num; } ;
struct TYPE_7__ {TYPE_1__ aspect_ratio; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ ASFContext ;

/* Variables and functions */
 size_t ASF_MAX_STREAMS ; 
 int asf_read_generic_value (int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  strcmp (size_t*,char*) ; 

__attribute__((used)) static int asf_store_aspect_ratio(AVFormatContext *s, uint8_t st_num, uint8_t *name, int type)
{
    ASFContext *asf   = s->priv_data;
    AVIOContext *pb   = s->pb;
    uint64_t value = 0;
    int ret;

    ret = asf_read_generic_value(pb, type, &value);
    if (ret < 0)
        return ret;

    if (st_num < ASF_MAX_STREAMS) {
        if (!strcmp(name, "AspectRatioX"))
            asf->asf_sd[st_num].aspect_ratio.num = value;
        else
            asf->asf_sd[st_num].aspect_ratio.den = value;
    }
    return 0;
}