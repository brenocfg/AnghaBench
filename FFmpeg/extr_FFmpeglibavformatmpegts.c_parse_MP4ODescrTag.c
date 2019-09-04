#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_1__ MP4DescrParseContext ;

/* Variables and functions */
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int parse_mp4_descr_arr (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_offsets (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int parse_MP4ODescrTag(MP4DescrParseContext *d, int64_t off, int len)
{
    int id_flags;
    if (len < 2)
        return 0;
    id_flags = avio_rb16(&d->pb);
    if (!(id_flags & 0x0020)) { // URL_Flag
        update_offsets(&d->pb, &off, &len);
        return parse_mp4_descr_arr(d, off, len); // ES_Descriptor[]
    } else {
        return 0;
    }
}