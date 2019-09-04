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
struct variant {int n_playlists; int bandwidth; struct playlist** playlists; } ;
struct playlist {int dummy; } ;
struct TYPE_9__ {TYPE_1__* priv_data; } ;
struct TYPE_8__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/  index; } ;
struct TYPE_7__ {int n_variants; struct variant** variants; } ;
typedef  TYPE_1__ HLSContext ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_program_add_stream_index (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_stream_to_programs(AVFormatContext *s, struct playlist *pls, AVStream *stream)
{
    HLSContext *c = s->priv_data;
    int i, j;
    int bandwidth = -1;

    for (i = 0; i < c->n_variants; i++) {
        struct variant *v = c->variants[i];

        for (j = 0; j < v->n_playlists; j++) {
            if (v->playlists[j] != pls)
                continue;

            av_program_add_stream_index(s, i, stream->index);

            if (bandwidth < 0)
                bandwidth = v->bandwidth;
            else if (bandwidth != v->bandwidth)
                bandwidth = -1; /* stream in multiple variants with different bandwidths */
        }
    }

    if (bandwidth >= 0)
        av_dict_set_int(&stream->metadata, "variant_bitrate", bandwidth, 0);
}