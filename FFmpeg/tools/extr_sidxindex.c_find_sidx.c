#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct Tracks {int nb_tracks; struct Track** tracks; } ;
struct Track {scalar_t__ sidx_start; int sidx_length; } ;
typedef  scalar_t__ int64_t ;
typedef  int int32_t ;
struct TYPE_7__ {int /*<<< orphan*/  eof_reached; } ;
typedef  TYPE_1__ AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 int MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_close (TYPE_1__*) ; 
 int avio_open2 (TYPE_1__**,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int avio_rb32 (TYPE_1__*) ; 
 scalar_t__ avio_seek (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (TYPE_1__*) ; 

__attribute__((used)) static int find_sidx(struct Tracks *tracks, int start_index,
                     const char *file)
{
    int err = 0;
    AVIOContext *f = NULL;
    int i;

    if ((err = avio_open2(&f, file, AVIO_FLAG_READ, NULL, NULL)) < 0)
        goto fail;

    while (!f->eof_reached) {
        int64_t pos = avio_tell(f);
        int32_t size, tag;

        size = avio_rb32(f);
        tag  = avio_rb32(f);
        if (size < 8)
            break;
        if (tag == MKBETAG('s', 'i', 'd', 'x')) {
            for (i = start_index; i < tracks->nb_tracks; i++) {
                struct Track *track = tracks->tracks[i];
                if (!track->sidx_start) {
                    track->sidx_start  = pos;
                    track->sidx_length = size;
                } else if (pos == track->sidx_start + track->sidx_length) {
                    track->sidx_length = pos + size - track->sidx_start;
                }
            }
        }
        if (avio_seek(f, pos + size, SEEK_SET) != pos + size)
            break;
    }

fail:
    if (f)
        avio_close(f);
    return err;
}