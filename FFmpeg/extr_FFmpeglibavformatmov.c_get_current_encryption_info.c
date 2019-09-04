#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ id; TYPE_3__* priv_data; } ;
struct TYPE_14__ {TYPE_1__* fc; int /*<<< orphan*/  frag_index; } ;
struct TYPE_13__ {scalar_t__ id; int /*<<< orphan*/ * encryption_index; } ;
struct TYPE_11__ {int /*<<< orphan*/ * encryption_index; int /*<<< orphan*/  default_encrypted_sample; } ;
struct TYPE_12__ {TYPE_2__ cenc; } ;
struct TYPE_10__ {int nb_streams; TYPE_6__** streams; } ;
typedef  TYPE_3__ MOVStreamContext ;
typedef  TYPE_4__ MOVFragmentStreamInfo ;
typedef  int /*<<< orphan*/  MOVEncryptionIndex ;
typedef  TYPE_5__ MOVContext ;
typedef  TYPE_6__ AVStream ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* av_mallocz (int) ; 
 TYPE_4__* get_current_frag_stream_info (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int get_current_encryption_info(MOVContext *c, MOVEncryptionIndex **encryption_index, MOVStreamContext **sc)
{
    MOVFragmentStreamInfo *frag_stream_info;
    AVStream *st;
    int i;

    frag_stream_info = get_current_frag_stream_info(&c->frag_index);
    if (frag_stream_info) {
        for (i = 0; i < c->fc->nb_streams; i++) {
            if (c->fc->streams[i]->id == frag_stream_info->id) {
              st = c->fc->streams[i];
              break;
            }
        }
        if (i == c->fc->nb_streams)
            return 0;
        *sc = st->priv_data;

        if (!frag_stream_info->encryption_index) {
            // If this stream isn't encrypted, don't create the index.
            if (!(*sc)->cenc.default_encrypted_sample)
                return 0;
            frag_stream_info->encryption_index = av_mallocz(sizeof(*frag_stream_info->encryption_index));
            if (!frag_stream_info->encryption_index)
                return AVERROR(ENOMEM);
        }
        *encryption_index = frag_stream_info->encryption_index;
        return 1;
    } else {
        // No current track fragment, using stream level encryption info.

        if (c->fc->nb_streams < 1)
            return 0;
        st = c->fc->streams[c->fc->nb_streams - 1];
        *sc = st->priv_data;

        if (!(*sc)->cenc.encryption_index) {
            // If this stream isn't encrypted, don't create the index.
            if (!(*sc)->cenc.default_encrypted_sample)
                return 0;
            (*sc)->cenc.encryption_index = av_mallocz(sizeof(*frag_stream_info->encryption_index));
            if (!(*sc)->cenc.encryption_index)
                return AVERROR(ENOMEM);
        }

        *encryption_index = (*sc)->cenc.encryption_index;
        return 1;
    }
}