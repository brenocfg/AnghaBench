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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * avf; int /*<<< orphan*/  list_pb; } ;
typedef  TYPE_1__ SegmentContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  avformat_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_format_io_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void seg_free(AVFormatContext *s)
{
    SegmentContext *seg = s->priv_data;
    ff_format_io_close(seg->avf, &seg->list_pb);
    avformat_free_context(seg->avf);
    seg->avf = NULL;
}