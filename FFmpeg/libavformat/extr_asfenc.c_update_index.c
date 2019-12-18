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
typedef  void* uint64_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
struct TYPE_7__ {int send_time; void* offset; void* packet_count; void* packet_number; } ;
struct TYPE_6__ {int next_start_sec; int nb_index_memory_alloc; void* next_packet_offset; void* next_packet_count; void* next_packet_number; int /*<<< orphan*/  maximum_packet; TYPE_4__* index_ptr; } ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASFContext ;

/* Variables and functions */
 int ASF_INDEX_BLOCK ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,void*) ; 
 int INT64_C (int) ; 
 int av_reallocp_array (TYPE_4__**,int,int) ; 

__attribute__((used)) static int update_index(AVFormatContext *s, int start_sec,
                         uint32_t packet_number, uint16_t packet_count,
                         uint64_t packet_offset)
{
    ASFContext *asf = s->priv_data;

    if (start_sec > asf->next_start_sec) {
        int i;

        if (!asf->next_start_sec) {
            asf->next_packet_number = packet_number;
            asf->next_packet_count  = packet_count;
            asf->next_packet_offset = packet_offset;
        }

        if (start_sec > asf->nb_index_memory_alloc) {
            int err;
            asf->nb_index_memory_alloc = (start_sec + ASF_INDEX_BLOCK) & ~(ASF_INDEX_BLOCK - 1);
            if ((err = av_reallocp_array(&asf->index_ptr,
                                         asf->nb_index_memory_alloc,
                                         sizeof(*asf->index_ptr))) < 0) {
                asf->nb_index_memory_alloc = 0;
                return err;
            }
        }
        for (i = asf->next_start_sec; i < start_sec; i++) {
            asf->index_ptr[i].packet_number = asf->next_packet_number;
            asf->index_ptr[i].packet_count  = asf->next_packet_count;
            asf->index_ptr[i].send_time     = asf->next_start_sec * INT64_C(10000000);
            asf->index_ptr[i].offset        = asf->next_packet_offset;

        }
    }
    asf->maximum_packet     = FFMAX(asf->maximum_packet, packet_count);
    asf->next_packet_number = packet_number;
    asf->next_packet_count  = packet_count;
    asf->next_packet_offset = packet_offset;
    asf->next_start_sec     = start_sec;

    return 0;
}