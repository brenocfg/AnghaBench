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
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {TYPE_4__* ahead; int /*<<< orphan*/  nsvs_timestamps; int /*<<< orphan*/  nsvs_file_offset; } ;
typedef  TYPE_1__ NSVContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_4__*) ; 

__attribute__((used)) static int nsv_read_close(AVFormatContext *s)
{
    NSVContext *nsv = s->priv_data;

    av_freep(&nsv->nsvs_file_offset);
    av_freep(&nsv->nsvs_timestamps);
    if (nsv->ahead[0].data)
        av_packet_unref(&nsv->ahead[0]);
    if (nsv->ahead[1].data)
        av_packet_unref(&nsv->ahead[1]);
    return 0;
}