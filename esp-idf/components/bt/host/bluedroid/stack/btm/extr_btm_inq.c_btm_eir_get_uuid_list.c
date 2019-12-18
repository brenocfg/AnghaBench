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

/* Variables and functions */
 int* BTM_CheckEirData (int*,int,int*) ; 
 int BTM_EIR_COMPLETE_128BITS_UUID_TYPE ; 
 int BTM_EIR_COMPLETE_16BITS_UUID_TYPE ; 
 int BTM_EIR_COMPLETE_32BITS_UUID_TYPE ; 
 int BTM_EIR_MORE_128BITS_UUID_TYPE ; 
 int BTM_EIR_MORE_16BITS_UUID_TYPE ; 
 int BTM_EIR_MORE_32BITS_UUID_TYPE ; 
#define  LEN_UUID_128 130 
#define  LEN_UUID_16 129 
#define  LEN_UUID_32 128 

__attribute__((used)) static UINT8 *btm_eir_get_uuid_list( UINT8 *p_eir, UINT8 uuid_size,
                                     UINT8 *p_num_uuid, UINT8 *p_uuid_list_type )
{
    UINT8   *p_uuid_data;
    UINT8   complete_type, more_type;
    UINT8   uuid_len;

    switch ( uuid_size ) {
    case LEN_UUID_16:
        complete_type = BTM_EIR_COMPLETE_16BITS_UUID_TYPE;
        more_type     = BTM_EIR_MORE_16BITS_UUID_TYPE;
        break;
    case LEN_UUID_32:
        complete_type = BTM_EIR_COMPLETE_32BITS_UUID_TYPE;
        more_type     = BTM_EIR_MORE_32BITS_UUID_TYPE;
        break;
    case LEN_UUID_128:
        complete_type = BTM_EIR_COMPLETE_128BITS_UUID_TYPE;
        more_type     = BTM_EIR_MORE_128BITS_UUID_TYPE;
        break;
    default:
        *p_num_uuid = 0;
        return NULL;
        break;
    }

    p_uuid_data = BTM_CheckEirData( p_eir, complete_type, &uuid_len );
    if (p_uuid_data == NULL) {
        p_uuid_data = BTM_CheckEirData( p_eir, more_type, &uuid_len );
        *p_uuid_list_type = more_type;
    } else {
        *p_uuid_list_type = complete_type;
    }

    *p_num_uuid = uuid_len / uuid_size;
    return p_uuid_data;
}