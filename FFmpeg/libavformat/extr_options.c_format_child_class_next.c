#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  const* priv_class; } ;
struct TYPE_7__ {int /*<<< orphan*/  const* priv_class; } ;
typedef  TYPE_1__ AVOutputFormat ;
typedef  TYPE_2__ AVInputFormat ;
typedef  int /*<<< orphan*/  AVClass ;

/* Variables and functions */
 TYPE_2__* av_iformat_next (TYPE_2__*) ; 
 TYPE_1__* av_oformat_next (TYPE_1__*) ; 
 int /*<<< orphan*/  const ff_avio_class ; 

__attribute__((used)) static const AVClass *format_child_class_next(const AVClass *prev)
{
    AVInputFormat  *ifmt = NULL;
    AVOutputFormat *ofmt = NULL;

    if (!prev)
        return &ff_avio_class;

    while ((ifmt = av_iformat_next(ifmt)))
        if (ifmt->priv_class == prev)
            break;

    if (!ifmt)
        while ((ofmt = av_oformat_next(ofmt)))
            if (ofmt->priv_class == prev)
                break;
    if (!ofmt)
        while (ifmt = av_iformat_next(ifmt))
            if (ifmt->priv_class)
                return ifmt->priv_class;

    while (ofmt = av_oformat_next(ofmt))
        if (ofmt->priv_class)
            return ofmt->priv_class;

    return NULL;
}