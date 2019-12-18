#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* value; } ;
struct TYPE_5__ {int /*<<< orphan*/  metadata; } ;
typedef  int /*<<< orphan*/  MOVMuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int atoi (char*) ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static int mov_write_trkn_tag(AVIOContext *pb, MOVMuxContext *mov,
                              AVFormatContext *s, int disc)
{
    AVDictionaryEntry *t = av_dict_get(s->metadata,
                                       disc ? "disc" : "track",
                                       NULL, 0);
    int size = 0, track = t ? atoi(t->value) : 0;
    if (track) {
        int tracks = 0;
        char *slash = strchr(t->value, '/');
        if (slash)
            tracks = atoi(slash + 1);
        avio_wb32(pb, 32); /* size */
        ffio_wfourcc(pb, disc ? "disk" : "trkn");
        avio_wb32(pb, 24); /* size */
        ffio_wfourcc(pb, "data");
        avio_wb32(pb, 0);        // 8 bytes empty
        avio_wb32(pb, 0);
        avio_wb16(pb, 0);        // empty
        avio_wb16(pb, track);    // track / disc number
        avio_wb16(pb, tracks);   // total track / disc number
        avio_wb16(pb, 0);        // empty
        size = 32;
    }
    return size;
}