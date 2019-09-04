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
struct TYPE_2__ {int /*<<< orphan*/  comment_count; int /*<<< orphan*/  comment_refs; int /*<<< orphan*/  name; int /*<<< orphan*/  descriptor_ref; int /*<<< orphan*/  package_uid; int /*<<< orphan*/  package_ul; int /*<<< orphan*/  tracks_count; int /*<<< orphan*/  tracks_refs; } ;
typedef  TYPE_1__ MXFPackage ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mxf_read_strong_ref_array (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mxf_read_utf16be_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxf_read_package(void *arg, AVIOContext *pb, int tag, int size, UID uid, int64_t klv_offset)
{
    MXFPackage *package = arg;
    switch(tag) {
    case 0x4403:
        return mxf_read_strong_ref_array(pb, &package->tracks_refs,
                                             &package->tracks_count);
    case 0x4401:
        /* UMID */
        avio_read(pb, package->package_ul, 16);
        avio_read(pb, package->package_uid, 16);
        break;
    case 0x4701:
        avio_read(pb, package->descriptor_ref, 16);
        break;
    case 0x4402:
        return mxf_read_utf16be_string(pb, size, &package->name);
    case 0x4406:
        return mxf_read_strong_ref_array(pb, &package->comment_refs,
                                             &package->comment_count);
    }
    return 0;
}