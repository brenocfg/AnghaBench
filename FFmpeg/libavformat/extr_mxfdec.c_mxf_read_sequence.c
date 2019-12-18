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
struct TYPE_2__ {int /*<<< orphan*/  structural_components_count; int /*<<< orphan*/  structural_components_refs; int /*<<< orphan*/  origin; int /*<<< orphan*/  data_definition_ul; int /*<<< orphan*/  duration; } ;
typedef  TYPE_1__ MXFSequence ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mxf_read_strong_ref_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxf_read_sequence(void *arg, AVIOContext *pb, int tag, int size, UID uid, int64_t klv_offset)
{
    MXFSequence *sequence = arg;
    switch(tag) {
    case 0x0202:
        sequence->duration = avio_rb64(pb);
        break;
    case 0x0201:
        avio_read(pb, sequence->data_definition_ul, 16);
        break;
        case 0x4b02:
        sequence->origin = avio_r8(pb);
        break;
    case 0x1001:
        return mxf_read_strong_ref_array(pb, &sequence->structural_components_refs,
                                             &sequence->structural_components_count);
    }
    return 0;
}