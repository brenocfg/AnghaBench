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
typedef  int UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*) ; 
 int /*<<< orphan*/  FALSE ; 
#define  LEN_UUID_128 130 
#define  LEN_UUID_16 129 
#define  LEN_UUID_32 128 
 int /*<<< orphan*/  STREAM_TO_UINT16 (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT32 (int,int*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static UINT16 btm_convert_uuid_to_uuid16( UINT8 *p_uuid, UINT8 uuid_size )
{
    static const UINT8  base_uuid[LEN_UUID_128] = {0xFB, 0x34, 0x9B, 0x5F, 0x80, 0x00, 0x00, 0x80,
                                                   0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                                  };
    UINT16 uuid16 = 0;
    UINT32 uuid32;
    BOOLEAN is_base_uuid;
    UINT8  xx;

    switch (uuid_size) {
    case LEN_UUID_16:
        STREAM_TO_UINT16 (uuid16, p_uuid);
        break;
    case LEN_UUID_32:
        STREAM_TO_UINT32 (uuid32, p_uuid);
        if (uuid32 < 0x10000) {
            uuid16 = (UINT16) uuid32;
        }
        break;
    case LEN_UUID_128:
        /* See if we can compress his UUID down to 16 or 32bit UUIDs */
        is_base_uuid = TRUE;
        for (xx = 0; xx < LEN_UUID_128 - 4; xx++) {
            if (p_uuid[xx] != base_uuid[xx]) {
                is_base_uuid = FALSE;
                break;
            }
        }
        if (is_base_uuid) {
            if ((p_uuid[LEN_UUID_128 - 1] == 0) && (p_uuid[LEN_UUID_128 - 2] == 0)) {
                p_uuid += (LEN_UUID_128 - 4);
                STREAM_TO_UINT16(uuid16, p_uuid);
            }
        }
        break;
    default:
        BTM_TRACE_WARNING("btm_convert_uuid_to_uuid16 invalid uuid size\n");
        break;
    }

    return ( uuid16);
}