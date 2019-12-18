#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_FLAG_READ ; 
 scalar_t__ av_get_frame_filename (char*,int,char const*,int) ; 
 scalar_t__ avio_check (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int find_image_range(AVIOContext *pb, int *pfirst_index, int *plast_index,
                            const char *path, int start_index, int start_index_range)
{
    char buf[1024];
    int range, last_index, range1, first_index;

    /* find the first image */
    for (first_index = start_index; first_index < start_index + start_index_range; first_index++) {
        if (av_get_frame_filename(buf, sizeof(buf), path, first_index) < 0) {
            *pfirst_index =
            *plast_index  = 1;
            if (pb || avio_check(buf, AVIO_FLAG_READ) > 0)
                return 0;
            return -1;
        }
        if (avio_check(buf, AVIO_FLAG_READ) > 0)
            break;
    }
    if (first_index == start_index + start_index_range)
        goto fail;

    /* find the last image */
    last_index = first_index;
    for (;;) {
        range = 0;
        for (;;) {
            if (!range)
                range1 = 1;
            else
                range1 = 2 * range;
            if (av_get_frame_filename(buf, sizeof(buf), path,
                                      last_index + range1) < 0)
                goto fail;
            if (avio_check(buf, AVIO_FLAG_READ) <= 0)
                break;
            range = range1;
            /* just in case... */
            if (range >= (1 << 30))
                goto fail;
        }
        /* we are sure than image last_index + range exists */
        if (!range)
            break;
        last_index += range;
    }
    *pfirst_index = first_index;
    *plast_index  = last_index;
    return 0;

fail:
    return -1;
}