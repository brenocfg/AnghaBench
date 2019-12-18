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
typedef  int /*<<< orphan*/  u32_t ;
typedef  int u16_t ;

/* Variables and functions */
 scalar_t__ ZM_CENC ; 
 scalar_t__ ZM_TKIP ; 
 int ZM_USER_KEY_DEFAULT ; 
 int /*<<< orphan*/  zfHpSetKey (int /*<<< orphan*/ *,int,int,scalar_t__,int*,int /*<<< orphan*/ *) ; 

u32_t zfHpSetApGroupKey(zdev_t* dev, u16_t* apMacAddr, u8_t type,
        u32_t* key, u32_t* micKey, u16_t vapId)
{
    zfHpSetKey(dev, ZM_USER_KEY_DEFAULT - 1 - vapId, 0, type, apMacAddr, key);	// 6D18 modify from 0 to 1 ??
            if ((type == ZM_TKIP)
#ifdef ZM_ENABLE_CENC
         || (type == ZM_CENC)
#endif //ZM_ENABLE_CENC
           )
        zfHpSetKey(dev, ZM_USER_KEY_DEFAULT - 1 - vapId, 1, type, apMacAddr, micKey);
    return 0;
}