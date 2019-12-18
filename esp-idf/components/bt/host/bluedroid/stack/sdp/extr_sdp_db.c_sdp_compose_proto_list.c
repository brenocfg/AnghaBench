#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_params; int protocol_uuid; int* params; } ;
typedef  TYPE_1__ tSDP_PROTOCOL_ELEM ;
typedef  int UINT8 ;
typedef  scalar_t__ UINT16 ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int DATA_ELE_SEQ_DESC_TYPE ; 
 scalar_t__ FALSE ; 
 int SIZE_IN_NEXT_BYTE ; 
 int SIZE_ONE_BYTE ; 
 int SIZE_TWO_BYTES ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UINT16_TO_BE_STREAM (int*,int) ; 
 int /*<<< orphan*/  UINT8_TO_BE_STREAM (int*,int) ; 
 int UINT_DESC_TYPE ; 
 int UUID_DESC_TYPE ; 
 scalar_t__ UUID_PROTOCOL_RFCOMM ; 

__attribute__((used)) static int sdp_compose_proto_list( UINT8 *p, UINT16 num_elem,
                                   tSDP_PROTOCOL_ELEM *p_elem_list)
{
    UINT16          xx, yy, len;
    BOOLEAN            is_rfcomm_scn;
    UINT8           *p_head = p;
    UINT8            *p_len;

    /* First, build the protocol list. This consists of a set of data element
    ** sequences, one for each layer. Each layer sequence consists of layer's
    ** UUID and optional parameters
    */
    for (xx = 0; xx < num_elem; xx++, p_elem_list++) {
        len = 3 + (p_elem_list->num_params * 3);
        UINT8_TO_BE_STREAM  (p, (DATA_ELE_SEQ_DESC_TYPE << 3) | SIZE_IN_NEXT_BYTE);

        p_len = p;
        *p++ = (UINT8) len;

        UINT8_TO_BE_STREAM  (p, (UUID_DESC_TYPE << 3) | SIZE_TWO_BYTES);
        UINT16_TO_BE_STREAM (p, p_elem_list->protocol_uuid);

        if (p_elem_list->protocol_uuid == UUID_PROTOCOL_RFCOMM) {
            is_rfcomm_scn = TRUE;
        } else {
            is_rfcomm_scn = FALSE;
        }

        for (yy = 0; yy < p_elem_list->num_params; yy++) {
            if (is_rfcomm_scn) {
                UINT8_TO_BE_STREAM  (p, (UINT_DESC_TYPE << 3) | SIZE_ONE_BYTE);
                UINT8_TO_BE_STREAM (p, p_elem_list->params[yy]);

                *p_len -= 1;
            } else {
                UINT8_TO_BE_STREAM  (p, (UINT_DESC_TYPE << 3) | SIZE_TWO_BYTES);
                UINT16_TO_BE_STREAM (p, p_elem_list->params[yy]);
            }
        }
    }
    return (p - p_head);
}