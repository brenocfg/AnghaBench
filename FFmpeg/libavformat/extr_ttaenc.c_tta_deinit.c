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
struct TYPE_4__ {int /*<<< orphan*/  queue_end; int /*<<< orphan*/  queue; int /*<<< orphan*/  seek_table; } ;
typedef  TYPE_1__ TTAMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_packet_list_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tta_deinit(AVFormatContext *s)
{
    TTAMuxContext *tta = s->priv_data;

    ffio_free_dyn_buf(&tta->seek_table);
    ff_packet_list_free(&tta->queue, &tta->queue_end);
}