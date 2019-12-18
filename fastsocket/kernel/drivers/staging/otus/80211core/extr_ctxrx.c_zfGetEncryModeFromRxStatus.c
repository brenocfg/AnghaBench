#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8_t ;
struct TYPE_3__ {int SAIndex; int DAIndex; } ;
struct TYPE_4__ {TYPE_1__ Data; } ;
struct zsAdditionInfo {TYPE_2__ Tail; } ;

/* Variables and functions */
#define  ZM_AES 134 
#define  ZM_CENC 133 
#define  ZM_NO_WEP 132 
#define  ZM_TKIP 131 
#define  ZM_WEP128 130 
#define  ZM_WEP256 129 
#define  ZM_WEP64 128 

u8_t zfGetEncryModeFromRxStatus(struct zsAdditionInfo* addInfo)
{
    u8_t securityByte;
    u8_t encryMode;

    securityByte = (addInfo->Tail.Data.SAIndex & 0xc0) >> 4;  /* byte4 */
    securityByte |= (addInfo->Tail.Data.DAIndex & 0xc0) >> 6; /* byte5 */

    switch( securityByte )
    {
        case ZM_NO_WEP:
        case ZM_WEP64:
        case ZM_WEP128:
        case ZM_WEP256:
#ifdef ZM_ENABLE_CENC
        case ZM_CENC:
#endif //ZM_ENABLE_CENC
        case ZM_TKIP:
        case ZM_AES:

            encryMode = securityByte;
            break;

        default:

            if ( (securityByte & 0xf8) == 0x08 )
            {
                // decrypted by software
            }

            encryMode = ZM_NO_WEP;
            break;
    }

    return encryMode;
}