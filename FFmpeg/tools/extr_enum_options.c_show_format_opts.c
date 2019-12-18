#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* class_name; } ;
struct TYPE_8__ {TYPE_3__* priv_class; } ;
struct TYPE_7__ {TYPE_3__* priv_class; } ;
typedef  TYPE_1__ AVOutputFormat ;
typedef  TYPE_2__ AVInputFormat ;

/* Variables and functions */
 TYPE_2__* av_demuxer_iterate (void**) ; 
 TYPE_1__* av_muxer_iterate (void**) ; 
 TYPE_3__* avformat_get_class () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_opts (TYPE_3__*) ; 

__attribute__((used)) static void show_format_opts(void)
{
    const AVInputFormat *iformat = NULL;
    const AVOutputFormat *oformat = NULL;
    void *iformat_opaque = NULL;
    void *oformat_opaque = NULL;

    printf("@section Generic format AVOptions\n");
    show_opts(avformat_get_class());

    printf("@section Format-specific AVOptions\n");
    while ((iformat = av_demuxer_iterate(&iformat_opaque))) {
        if (!iformat->priv_class)
            continue;
        printf("@subsection %s AVOptions\n", iformat->priv_class->class_name);
        show_opts(iformat->priv_class);
    }
    while ((oformat = av_muxer_iterate(&oformat_opaque))) {
        if (!oformat->priv_class)
            continue;
        printf("@subsection %s AVOptions\n", oformat->priv_class->class_name);
        show_opts(oformat->priv_class);
    }
}