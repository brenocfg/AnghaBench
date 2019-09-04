#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* fc; } ;
struct TYPE_8__ {int /*<<< orphan*/  timecode_track; } ;
struct TYPE_7__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_6__ {TYPE_3__* priv_data; } ;
typedef  TYPE_3__ MOVStreamContext ;
typedef  TYPE_4__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_read_tmcd(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    MOVStreamContext *sc;

    if (c->fc->nb_streams < 1)
        return AVERROR_INVALIDDATA;
    sc = c->fc->streams[c->fc->nb_streams - 1]->priv_data;
    sc->timecode_track = avio_rb32(pb);
    return 0;
}