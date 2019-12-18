#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flag; int /*<<< orphan*/  str; } ;
struct TYPE_7__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_6__ {int disposition; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char*) ; 
 TYPE_4__* ff_nut_dispositions ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void set_disposition_bits(AVFormatContext *avf, char *value,
                                 int stream_id)
{
    int flag = 0, i;

    for (i = 0; ff_nut_dispositions[i].flag; ++i)
        if (!strcmp(ff_nut_dispositions[i].str, value))
            flag = ff_nut_dispositions[i].flag;
    if (!flag)
        av_log(avf, AV_LOG_INFO, "unknown disposition type '%s'\n", value);
    for (i = 0; i < avf->nb_streams; ++i)
        if (stream_id == i || stream_id == -1)
            avf->streams[i]->disposition |= flag;
}