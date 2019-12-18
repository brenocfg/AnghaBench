#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  hb_work_private_t ;
struct TYPE_4__ {int* data; } ;
typedef  TYPE_1__ hb_buffer_t ;

/* Variables and functions */
 TYPE_1__* hb_buffer_init (int) ; 

__attribute__((used)) static hb_buffer_t * cc_fill_buffer(hb_work_private_t *pv, uint8_t *cc, int size)
{
    int cc_count[4] = {0,};
    int ii;
    hb_buffer_t *buf = NULL;

    for (ii = 0; ii < size; ii += 3)
    {
        if ((cc[ii] & 0x04) == 0)    // not valid
            continue;
        if ((cc[ii+1] & 0x7f) == 0 && (cc[ii+2] & 0x7f) == 0) // stuffing
            continue;
        int type = cc[ii] & 0x03;
        cc_count[type]++;
    }

    // Only handles CC1 for now.
    if (cc_count[0] > 0)
    {
        buf = hb_buffer_init(cc_count[0] * 2);
        int jj = 0;
        for (ii = 0; ii < size; ii += 3)
        {
            if ((cc[ii] & 0x04) == 0)    // not valid
                continue;
            if ((cc[ii+1] & 0x7f) == 0 && (cc[ii+2] & 0x7f) == 0) // stuffing
                continue;
            int type = cc[ii] & 0x03;
            if (type == 0)
            {
                buf->data[jj++] = cc[ii+1];
                buf->data[jj++] = cc[ii+2];
            }
        }
    }
    return buf;
}