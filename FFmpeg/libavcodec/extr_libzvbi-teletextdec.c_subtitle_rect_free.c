#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* ass; struct TYPE_4__** data; } ;
typedef  TYPE_1__ AVSubtitleRect ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

__attribute__((used)) static void subtitle_rect_free(AVSubtitleRect **sub_rect)
{
    av_freep(&(*sub_rect)->data[0]);
    av_freep(&(*sub_rect)->data[1]);
    av_freep(&(*sub_rect)->ass);
    av_freep(sub_rect);
}