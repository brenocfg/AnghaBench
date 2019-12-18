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
typedef  void* int64_t ;
struct TYPE_11__ {int nb_streams; TYPE_1__** streams; TYPE_4__* priv_data; } ;
struct TYPE_10__ {void* riff_start; int /*<<< orphan*/  riff_id; } ;
struct TYPE_8__ {scalar_t__ entry; int /*<<< orphan*/  audio_strm_offset; } ;
struct TYPE_9__ {TYPE_2__ indexes; int /*<<< orphan*/  audio_strm_length; } ;
struct TYPE_7__ {TYPE_3__* priv_data; } ;
typedef  TYPE_3__ AVIStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVIContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 void* ff_start_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int64_t avi_start_new_riff(AVFormatContext *s, AVIOContext *pb,
                                  const char *riff_tag, const char *list_tag)
{
    AVIContext *avi = s->priv_data;
    int64_t loff;
    int i;

    avi->riff_id++;
    for (i = 0; i < s->nb_streams; i++) {
        AVIStream *avist = s->streams[i]->priv_data;
        avist->indexes.audio_strm_offset = avist->audio_strm_length;
        avist->indexes.entry = 0;
    }

    avi->riff_start = ff_start_tag(pb, "RIFF");
    ffio_wfourcc(pb, riff_tag);
    loff = ff_start_tag(pb, "LIST");
    ffio_wfourcc(pb, list_tag);
    return loff;
}