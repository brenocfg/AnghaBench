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
struct TYPE_3__ {int code1; int /*<<< orphan*/  code; } ;
typedef  TYPE_1__ RangeCoder ;
typedef  int /*<<< orphan*/  GetByteContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_get_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sync_code3(GetByteContext *gb, RangeCoder *rc)
{
    rc->code1++;
    if (rc->code1 == 0x20000) {
        rc->code = bytestream2_get_le32(gb);
        rc->code1 = 0;
    }
}