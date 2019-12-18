#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_8__** bsfs; TYPE_2__* avf; } ;
typedef  TYPE_6__ TeeSlave ;
struct TYPE_18__ {TYPE_5__* filter; } ;
struct TYPE_17__ {TYPE_3__* codecpar; } ;
struct TYPE_15__ {char* name; TYPE_4__* priv_class; } ;
struct TYPE_14__ {char* (* item_name ) (TYPE_8__*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  codec_type; int /*<<< orphan*/  codec_id; } ;
struct TYPE_12__ {int nb_streams; TYPE_7__** streams; TYPE_1__* oformat; int /*<<< orphan*/  url; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_7__ AVStream ;
typedef  TYPE_8__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_get_media_type_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (void*,int,char*,...) ; 
 int /*<<< orphan*/  avcodec_get_name (int /*<<< orphan*/ ) ; 
 char* stub1 (TYPE_8__*) ; 

__attribute__((used)) static void log_slave(TeeSlave *slave, void *log_ctx, int log_level)
{
    int i;
    av_log(log_ctx, log_level, "filename:'%s' format:%s\n",
           slave->avf->url, slave->avf->oformat->name);
    for (i = 0; i < slave->avf->nb_streams; i++) {
        AVStream *st = slave->avf->streams[i];
        AVBSFContext *bsf = slave->bsfs[i];
        const char *bsf_name;

        av_log(log_ctx, log_level, "    stream:%d codec:%s type:%s",
               i, avcodec_get_name(st->codecpar->codec_id),
               av_get_media_type_string(st->codecpar->codec_type));

        bsf_name = bsf->filter->priv_class ?
                   bsf->filter->priv_class->item_name(bsf) : bsf->filter->name;
        av_log(log_ctx, log_level, " bsfs: %s\n", bsf_name);
    }
}