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
typedef  char* UINT32 ;
typedef  char* UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_DEBUG (char*,...) ; 
 int /*<<< orphan*/  BTM_TRACE_WARNING (char*,int,int) ; 
 int LEN_UUID_128 ; 
 int LEN_UUID_16 ; 
 int LEN_UUID_32 ; 
 int /*<<< orphan*/  STREAM_TO_ARRAY16 (int*,int*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT16 (char*,int*) ; 
 int /*<<< orphan*/  STREAM_TO_UINT32 (char*,int*) ; 
 int* btm_eir_get_uuid_list (int*,int,int*,int*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

UINT8 BTM_GetEirUuidList( UINT8 *p_eir, UINT8 uuid_size, UINT8 *p_num_uuid,
                          UINT8 *p_uuid_list, UINT8 max_num_uuid)
{
    UINT8   *p_uuid_data;
    UINT8   type;
    UINT8   yy, xx;
    UINT16  *p_uuid16 = (UINT16 *)p_uuid_list;
    UINT32  *p_uuid32 = (UINT32 *)p_uuid_list;
    char    buff[LEN_UUID_128 * 2 + 1];

    p_uuid_data = btm_eir_get_uuid_list( p_eir, uuid_size, p_num_uuid, &type );
    if ( p_uuid_data == NULL ) {
        return 0x00;
    }

    if ( *p_num_uuid > max_num_uuid ) {
        BTM_TRACE_WARNING("BTM_GetEirUuidList number of uuid in EIR = %d, size of uuid list = %d\n",
                          *p_num_uuid, max_num_uuid );
        *p_num_uuid = max_num_uuid;
    }

    BTM_TRACE_DEBUG("BTM_GetEirUuidList type = %02X, number of uuid = %d\n", type, *p_num_uuid );

    if ( uuid_size == LEN_UUID_16 ) {
        for ( yy = 0; yy < *p_num_uuid; yy++ ) {
            STREAM_TO_UINT16(*(p_uuid16 + yy), p_uuid_data);
            BTM_TRACE_DEBUG("                     0x%04X\n", *(p_uuid16 + yy));
        }
    } else if ( uuid_size == LEN_UUID_32 ) {
        for ( yy = 0; yy < *p_num_uuid; yy++ ) {
            STREAM_TO_UINT32(*(p_uuid32 + yy), p_uuid_data);
            BTM_TRACE_DEBUG("                     0x%08X\n", *(p_uuid32 + yy));
        }
    } else if ( uuid_size == LEN_UUID_128 ) {
        for ( yy = 0; yy < *p_num_uuid; yy++ ) {
            STREAM_TO_ARRAY16(p_uuid_list + yy * LEN_UUID_128, p_uuid_data);
            for ( xx = 0; xx < LEN_UUID_128; xx++ ) {
                sprintf(buff + xx * 2, "%02X", *(p_uuid_list + yy * LEN_UUID_128 + xx));
            }
            BTM_TRACE_DEBUG("                     0x%s\n", buff);
        }
    }

    return type;
}