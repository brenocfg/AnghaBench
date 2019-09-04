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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;
struct TYPE_5__ {int next_start_sec; TYPE_1__* index_ptr; scalar_t__ data_offset; } ;
struct TYPE_4__ {scalar_t__ send_time; scalar_t__ offset; } ;
typedef  TYPE_2__ ASFContext ;

/* Variables and functions */
 scalar_t__ DATA_HEADER_SIZE ; 

__attribute__((used)) static int32_t get_send_time(ASFContext *asf, int64_t pres_time, uint64_t *offset)
{
    int i;
    int32_t send_time = 0;
    *offset = asf->data_offset + DATA_HEADER_SIZE;
    for (i = 0; i < asf->next_start_sec; i++) {
        if (pres_time <= asf->index_ptr[i].send_time)
            break;
        send_time = asf->index_ptr[i].send_time;
        *offset   = asf->index_ptr[i].offset;
    }

    return send_time / 10000;
}