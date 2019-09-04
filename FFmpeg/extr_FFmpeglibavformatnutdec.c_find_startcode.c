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
typedef  scalar_t__ uint64_t ;
typedef  int int64_t ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int avio_tell (int /*<<< orphan*/ *) ; 
 scalar_t__ find_any_startcode (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int64_t find_startcode(AVIOContext *bc, uint64_t code, int64_t pos)
{
    for (;;) {
        uint64_t startcode = find_any_startcode(bc, pos);
        if (startcode == code)
            return avio_tell(bc) - 8;
        else if (startcode == 0)
            return -1;
        pos = -1;
    }
}