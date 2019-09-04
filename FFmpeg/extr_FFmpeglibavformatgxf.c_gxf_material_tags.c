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
typedef  void* uint32_t ;
struct gxf_stream_info {void* last_field; void* first_field; } ;
typedef  scalar_t__ GXFMatTag ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 scalar_t__ MAT_FIRST_FIELD ; 
 scalar_t__ MAT_LAST_FIELD ; 
 void* avio_r8 (int /*<<< orphan*/ *) ; 
 void* avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gxf_material_tags(AVIOContext *pb, int *len, struct gxf_stream_info *si) {
    si->first_field = AV_NOPTS_VALUE;
    si->last_field = AV_NOPTS_VALUE;
    while (*len >= 2) {
        GXFMatTag tag = avio_r8(pb);
        int tlen = avio_r8(pb);
        *len -= 2;
        if (tlen > *len)
            return;
        *len -= tlen;
        if (tlen == 4) {
            uint32_t value = avio_rb32(pb);
            if (tag == MAT_FIRST_FIELD)
                si->first_field = value;
            else if (tag == MAT_LAST_FIELD)
                si->last_field = value;
        } else
            avio_skip(pb, tlen);
    }
}