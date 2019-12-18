#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  UID ;
struct TYPE_2__ {int /*<<< orphan*/  structural_components_count; int /*<<< orphan*/  structural_components_refs; int /*<<< orphan*/  duration; } ;
typedef  TYPE_1__ MXFEssenceGroup ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_rb64 (int /*<<< orphan*/ *) ; 
 int mxf_read_strong_ref_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxf_read_essence_group(void *arg, AVIOContext *pb, int tag, int size, UID uid, int64_t klv_offset)
{
    MXFEssenceGroup *essence_group = arg;
    switch (tag) {
    case 0x0202:
        essence_group->duration = avio_rb64(pb);
        break;
    case 0x0501:
        return mxf_read_strong_ref_array(pb, &essence_group->structural_components_refs,
                                             &essence_group->structural_components_count);
    }
    return 0;
}