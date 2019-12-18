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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ MXFTaggedValue ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mxf_indirect_value_utf16be ; 
 int /*<<< orphan*/  mxf_indirect_value_utf16le ; 
 int mxf_read_utf16be_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int mxf_read_utf16le_string (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mxf_read_indirect_value(void *arg, AVIOContext *pb, int size)
{
    MXFTaggedValue *tagged_value = arg;
    uint8_t key[17];

    if (size <= 17)
        return 0;

    avio_read(pb, key, 17);
    /* TODO: handle other types of of indirect values */
    if (memcmp(key, mxf_indirect_value_utf16le, 17) == 0) {
        return mxf_read_utf16le_string(pb, size - 17, &tagged_value->value);
    } else if (memcmp(key, mxf_indirect_value_utf16be, 17) == 0) {
        return mxf_read_utf16be_string(pb, size - 17, &tagged_value->value);
    }
    return 0;
}