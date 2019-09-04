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
struct TYPE_4__ {int /*<<< orphan*/  a53_caption; scalar_t__ a53_caption_size; } ;
struct TYPE_5__ {TYPE_1__ a53_caption; } ;
typedef  TYPE_2__ HEVCSEI ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

void ff_hevc_reset_sei(HEVCSEI *s)
{
    s->a53_caption.a53_caption_size = 0;
    av_freep(&s->a53_caption.a53_caption);
}