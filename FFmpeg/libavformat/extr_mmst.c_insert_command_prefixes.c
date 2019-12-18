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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  write_out_ptr; } ;
typedef  TYPE_1__ MMSContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream_put_le32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void insert_command_prefixes(MMSContext *mms,
        uint32_t prefix1, uint32_t prefix2)
{
    bytestream_put_le32(&mms->write_out_ptr, prefix1); // first prefix
    bytestream_put_le32(&mms->write_out_ptr, prefix2); // second prefix
}