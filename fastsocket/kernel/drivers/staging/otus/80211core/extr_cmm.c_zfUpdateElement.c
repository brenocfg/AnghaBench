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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  scalar_t__ u8_t ;
typedef  scalar_t__ u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  zfMemoryMove (scalar_t__*,scalar_t__*,scalar_t__) ; 

u16_t zfUpdateElement(zdev_t* dev, u8_t* buf, u16_t size, u8_t* updateeid)
{
    u16_t offset = 0;
    u16_t elen;

    while (offset < size) {
        elen = *(buf+offset+1);

        if (*(buf+offset) == updateeid[0]) {
            if (updateeid[1] <= elen) {
                zfMemoryMove(buf+offset, updateeid, updateeid[1]+2);
                zfMemoryMove(buf+offset+updateeid[1]+2, buf+offset+elen+2, size-offset-elen-2);

                return size-(elen-updateeid[1]);
            } else {
                zfMemoryMove(buf+offset+updateeid[1]+2, buf+offset+elen+2, size-offset-elen-2);
                zfMemoryMove(buf+offset, updateeid, updateeid[1]+2);

                return size+(updateeid[1]-elen);
            }
        }

        offset += (elen+2);
    }

    return size;
}