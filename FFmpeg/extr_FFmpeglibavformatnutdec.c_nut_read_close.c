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
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {int header_count; int /*<<< orphan*/ * header; int /*<<< orphan*/  stream; int /*<<< orphan*/  time_base; } ;
typedef  TYPE_1__ NUTContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_nut_free_sp (TYPE_1__*) ; 

__attribute__((used)) static int nut_read_close(AVFormatContext *s)
{
    NUTContext *nut = s->priv_data;
    int i;

    av_freep(&nut->time_base);
    av_freep(&nut->stream);
    ff_nut_free_sp(nut);
    for (i = 1; i < nut->header_count; i++)
        av_freep(&nut->header[i]);

    return 0;
}