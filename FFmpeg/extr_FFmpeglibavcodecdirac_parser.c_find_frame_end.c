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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int state; int is_synced; int header_bytes_needed; int sync_offset; } ;
typedef  TYPE_1__ DiracParseContext ;

/* Variables and functions */
 int DIRAC_PARSE_INFO_PREFIX ; 

__attribute__((used)) static int find_frame_end(DiracParseContext *pc,
                          const uint8_t *buf, int buf_size)
{
    uint32_t state = pc->state;
    int i = 0;

    if (!pc->is_synced) {
        for (i = 0; i < buf_size; i++) {
            state = (state << 8) | buf[i];
            if (state == DIRAC_PARSE_INFO_PREFIX) {
                state                   = -1;
                pc->is_synced           = 1;
                pc->header_bytes_needed = 9;
                pc->sync_offset         = i;
                break;
            }
        }
    }

    if (pc->is_synced) {
        pc->sync_offset = 0;
        for (; i < buf_size; i++) {
            if (state == DIRAC_PARSE_INFO_PREFIX) {
                if ((buf_size - i) >= pc->header_bytes_needed) {
                    pc->state = -1;
                    return i + pc->header_bytes_needed;
                } else {
                    pc->header_bytes_needed = 9 - (buf_size - i);
                    break;
                }
            } else
                state = (state << 8) | buf[i];
        }
    }
    pc->state = state;
    return -1;
}