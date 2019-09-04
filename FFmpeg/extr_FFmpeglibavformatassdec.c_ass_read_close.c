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
struct TYPE_5__ {int /*<<< orphan*/  q; } ;
struct TYPE_4__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ ASSContext ;

/* Variables and functions */
 int /*<<< orphan*/  ff_subtitles_queue_clean (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ass_read_close(AVFormatContext *s)
{
    ASSContext *ass = s->priv_data;
    ff_subtitles_queue_clean(&ass->q);
    return 0;
}