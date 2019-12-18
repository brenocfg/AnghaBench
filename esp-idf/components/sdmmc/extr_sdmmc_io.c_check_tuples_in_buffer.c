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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ CISTPL_CODE_END ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static bool check_tuples_in_buffer(uint8_t* buf, int buffer_size, int* inout_cis_offset)
{
    int cis_offset = *inout_cis_offset;
    if (cis_offset == -1) {
        //the CIS code is checked in the last buffer, skip to next tuple
        cis_offset += buf[0] + 2;
    }
    assert(cis_offset >= 0);
    while (1) {
        if (cis_offset < buffer_size) {
            //A CIS code in the buffer, check it
            if (buf[cis_offset] == CISTPL_CODE_END) {
                *inout_cis_offset = cis_offset + 1;
                return true;
            }
        }
        if (cis_offset + 1 < buffer_size) {
            cis_offset += buf[cis_offset+1] + 2;
        } else {
            break;
        }
    }
    *inout_cis_offset = cis_offset;
    return false;
}