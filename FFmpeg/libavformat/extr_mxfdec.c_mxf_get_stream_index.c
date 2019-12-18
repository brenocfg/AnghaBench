#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mxf_essence_element_key ;
struct TYPE_10__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_9__ {scalar_t__ key; } ;
struct TYPE_8__ {int body_sid; int /*<<< orphan*/  track_number; } ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ MXFTrack ;
typedef  TYPE_3__ KLVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mxf_get_stream_index(AVFormatContext *s, KLVPacket *klv, int body_sid)
{
    int i;

    for (i = 0; i < s->nb_streams; i++) {
        MXFTrack *track = s->streams[i]->priv_data;
        /* SMPTE 379M 7.3 */
        if (track && (!body_sid || !track->body_sid || track->body_sid == body_sid) && !memcmp(klv->key + sizeof(mxf_essence_element_key), track->track_number, sizeof(track->track_number)))
            return i;
    }
    /* return 0 if only one stream, for OP Atom files with 0 as track number */
    return s->nb_streams == 1 && s->streams[0]->priv_data ? 0 : -1;
}