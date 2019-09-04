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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  UID ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/ * av_calloc (int,int) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mxf_read_strong_ref_array(AVIOContext *pb, UID **refs, int *count)
{
    *count = avio_rb32(pb);
    *refs = av_calloc(*count, sizeof(UID));
    if (!*refs) {
        *count = 0;
        return AVERROR(ENOMEM);
    }
    avio_skip(pb, 4); /* useless size of objects, always 16 according to specs */
    avio_read(pb, (uint8_t *)*refs, *count * sizeof(UID));
    return 0;
}