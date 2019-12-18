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
struct TYPE_7__ {struct TYPE_7__* skipped_bytes_pos; } ;
struct TYPE_5__ {scalar_t__ rbsp_buffer_size; scalar_t__ rbsp_buffer_alloc_size; TYPE_4__* rbsp_buffer; scalar_t__ rbsp_buffer_ref; } ;
struct TYPE_6__ {int nals_allocated; int nal_buffer_size; TYPE_1__ rbsp; TYPE_4__* nals; } ;
typedef  TYPE_2__ H2645Packet ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (scalar_t__*) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 

void ff_h2645_packet_uninit(H2645Packet *pkt)
{
    int i;
    for (i = 0; i < pkt->nals_allocated; i++) {
        av_freep(&pkt->nals[i].skipped_bytes_pos);
    }
    av_freep(&pkt->nals);
    pkt->nals_allocated = pkt->nal_buffer_size = 0;
    if (pkt->rbsp.rbsp_buffer_ref) {
        av_buffer_unref(&pkt->rbsp.rbsp_buffer_ref);
        pkt->rbsp.rbsp_buffer = NULL;
    } else
        av_freep(&pkt->rbsp.rbsp_buffer);
    pkt->rbsp.rbsp_buffer_alloc_size = pkt->rbsp.rbsp_buffer_size = 0;
}