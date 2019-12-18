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
typedef  int /*<<< orphan*/  zbuf_t ;
typedef  int u8_t ;
typedef  int /*<<< orphan*/  u16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZM_ICV_SUCCESS ; 
 int /*<<< orphan*/  zfWEPDecrypt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*,int*) ; 

u16_t zfTKIPDecrypt(zdev_t *dev, zbuf_t *buf, u16_t offset, u8_t keyLen, u8_t* key)
{
    u16_t ret = ZM_ICV_SUCCESS;
    u8_t iv[3];

    iv[0] = key[0];
    iv[1] = key[1];
    iv[2] = key[2];

    keyLen -= 3;

    ret = zfWEPDecrypt(dev, buf, offset, keyLen, &key[3], iv);

    return ret;
}