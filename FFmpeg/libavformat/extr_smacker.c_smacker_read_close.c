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
struct TYPE_4__ {int /*<<< orphan*/  frm_flags; int /*<<< orphan*/  frm_size; int /*<<< orphan*/ * bufs; } ;
typedef  TYPE_1__ SmackerContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smacker_read_close(AVFormatContext *s)
{
    SmackerContext *smk = s->priv_data;
    int i;

    for(i = 0; i < 7; i++)
        av_freep(&smk->bufs[i]);
    av_freep(&smk->frm_size);
    av_freep(&smk->frm_flags);

    return 0;
}