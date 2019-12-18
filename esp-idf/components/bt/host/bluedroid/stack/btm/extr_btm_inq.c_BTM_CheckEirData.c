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
typedef  scalar_t__ UINT8 ;

/* Variables and functions */
 int /*<<< orphan*/  BTM_TRACE_API (char*,scalar_t__) ; 
 int HCI_EXT_INQ_RESPONSE_LEN ; 
 int /*<<< orphan*/  STREAM_TO_UINT8 (scalar_t__,scalar_t__*) ; 

UINT8 *BTM_CheckEirData( UINT8 *p_eir, UINT8 type, UINT8 *p_length )
{
    UINT8 *p = p_eir;
    UINT8 length;
    UINT8 eir_type;
    BTM_TRACE_API("BTM_CheckEirData type=0x%02X\n", type);

    STREAM_TO_UINT8(length, p);
    while ( length && (p - p_eir <= HCI_EXT_INQ_RESPONSE_LEN)) {
        STREAM_TO_UINT8(eir_type, p);
        if ( eir_type == type ) {
            /* length doesn't include itself */
            *p_length = length - 1; /* minus the length of type */
            return p;
        }
        p += length - 1; /* skip the length of data */
        STREAM_TO_UINT8(length, p);
    }

    *p_length = 0;
    return NULL;
}