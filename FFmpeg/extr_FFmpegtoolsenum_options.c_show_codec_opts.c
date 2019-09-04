#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* class_name; } ;
struct TYPE_6__ {TYPE_2__* priv_class; } ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 TYPE_1__* av_codec_next (TYPE_1__*) ; 
 TYPE_2__* avcodec_get_class () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_opts (TYPE_2__*) ; 

__attribute__((used)) static void show_codec_opts(void)
{
    AVCodec *c = NULL;

    printf("@section Generic codec AVOptions\n");
    show_opts(avcodec_get_class());

    printf("@section Codec-specific AVOptions\n");
    while ((c = av_codec_next(c))) {
        if (!c->priv_class)
            continue;
        printf("@subsection %s AVOptions\n", c->priv_class->class_name);
        show_opts(c->priv_class);
    }
}