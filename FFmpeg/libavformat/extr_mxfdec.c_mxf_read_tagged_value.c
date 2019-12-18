#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  UID ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ MXFTaggedValue ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int mxf_read_indirect_value (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int mxf_read_utf16be_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxf_read_tagged_value(void *arg, AVIOContext *pb, int tag, int size, UID uid, int64_t klv_offset)
{
    MXFTaggedValue *tagged_value = arg;
    switch (tag){
    case 0x5001:
        return mxf_read_utf16be_string(pb, size, &tagged_value->name);
    case 0x5003:
        return mxf_read_indirect_value(tagged_value, pb, size);
    }
    return 0;
}