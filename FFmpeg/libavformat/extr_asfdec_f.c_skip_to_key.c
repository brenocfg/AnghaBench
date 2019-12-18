#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* asfid2avid; TYPE_4__* streams; } ;
struct TYPE_10__ {int skip_to_key; } ;
struct TYPE_9__ {TYPE_2__** streams; TYPE_5__* priv_data; } ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ ASFStream ;
typedef  TYPE_5__ ASFContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 

__attribute__((used)) static void skip_to_key(AVFormatContext *s)
{
    ASFContext *asf = s->priv_data;
    int i;

    for (i = 0; i < 128; i++) {
        int j = asf->asfid2avid[i];
        ASFStream *asf_st = &asf->streams[i];
        if (j < 0 || s->streams[j]->codecpar->codec_type != AVMEDIA_TYPE_VIDEO)
            continue;

        asf_st->skip_to_key = 1;
    }
}