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
typedef  int u32_t ;
typedef  int u16_t ;

/* Variables and functions */
 scalar_t__ ZM_CENC ; 
 scalar_t__ ZM_TKIP ; 
 int /*<<< orphan*/  zfHpSetKey (int /*<<< orphan*/ *,int,int,scalar_t__,int*,int*) ; 

u32_t zfHpSetApPairwiseKey(zdev_t* dev, u16_t* staMacAddr, u8_t type,
        u32_t* key, u32_t* micKey, u16_t staAid)
{
    if ((staAid!=0) && (staAid<64))
    {
        zfHpSetKey(dev, (staAid-1), 0, type, staMacAddr, key);
                if ((type == ZM_TKIP)
#ifdef ZM_ENABLE_CENC
         || (type == ZM_CENC)
#endif //ZM_ENABLE_CENC
           )
            zfHpSetKey(dev, (staAid-1), 1, type, staMacAddr, micKey);
        return 0;
    }
    return 1;
}