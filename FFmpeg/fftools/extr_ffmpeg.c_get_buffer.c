#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* opaque; } ;
struct TYPE_11__ {scalar_t__ format; } ;
struct TYPE_10__ {int (* hwaccel_get_buffer ) (TYPE_3__*,TYPE_2__*,int) ;scalar_t__ hwaccel_pix_fmt; } ;
typedef  TYPE_1__ InputStream ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int avcodec_default_get_buffer2 (TYPE_3__*,TYPE_2__*,int) ; 
 int stub1 (TYPE_3__*,TYPE_2__*,int) ; 

__attribute__((used)) static int get_buffer(AVCodecContext *s, AVFrame *frame, int flags)
{
    InputStream *ist = s->opaque;

    if (ist->hwaccel_get_buffer && frame->format == ist->hwaccel_pix_fmt)
        return ist->hwaccel_get_buffer(s, frame, flags);

    return avcodec_default_get_buffer2(s, frame, flags);
}