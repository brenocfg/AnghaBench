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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_8__ {int ism_lookahead; } ;
struct TYPE_7__ {int nb_frag_info; } ;
typedef  TYPE_1__ MOVTrack ;
typedef  TYPE_2__ MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mov_write_tfrf_tag (int /*<<< orphan*/ *,TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static int mov_write_tfrf_tags(AVIOContext *pb, MOVMuxContext *mov,
                               MOVTrack *track)
{
    int64_t pos = avio_tell(pb);
    int i;
    for (i = 0; i < mov->ism_lookahead; i++) {
        /* Update the tfrf tag for the last ism_lookahead fragments,
         * nb_frag_info - 1 is the next fragment to be written. */
        mov_write_tfrf_tag(pb, mov, track, track->nb_frag_info - 2 - i);
    }
    avio_seek(pb, pos, SEEK_SET);
    return 0;
}