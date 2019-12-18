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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  UINT16 ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_ID_BT_PROFILE_DESC_LIST ; 
 int DATA_ELE_SEQ_DESC_TYPE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SDP_AddAttribute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int SDP_MAX_ATTR_LEN ; 
 int /*<<< orphan*/  SDP_TRACE_ERROR (char*) ; 
 int SIZE_IN_NEXT_BYTE ; 
 int SIZE_TWO_BYTES ; 
 int /*<<< orphan*/  UINT16_TO_BE_STREAM (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINT8_TO_BE_STREAM (scalar_t__*,int) ; 
 int UINT_DESC_TYPE ; 
 int UUID_DESC_TYPE ; 
 int /*<<< orphan*/  osi_free (scalar_t__*) ; 
 scalar_t__ osi_malloc (int) ; 

BOOLEAN SDP_AddProfileDescriptorList (UINT32 handle, UINT16 profile_uuid,
                                      UINT16 version)
{
#if SDP_SERVER_ENABLED == TRUE
    UINT8           *p_buff;
    UINT8           *p;
    BOOLEAN        result;

    if ((p_buff = (UINT8 *) osi_malloc(sizeof(UINT8) * SDP_MAX_ATTR_LEN)) == NULL) {
        SDP_TRACE_ERROR("SDP_AddProfileDescriptorList cannot get a buffer!\n");
        return (FALSE);
    }
    p = p_buff + 2;

    /* First, build the profile descriptor list. This consists of a data element sequence. */
    /* The sequence consists of profile's UUID and version number  */
    UINT8_TO_BE_STREAM  (p, (UUID_DESC_TYPE << 3) | SIZE_TWO_BYTES);
    UINT16_TO_BE_STREAM (p, profile_uuid);

    UINT8_TO_BE_STREAM  (p, (UINT_DESC_TYPE << 3) | SIZE_TWO_BYTES);
    UINT16_TO_BE_STREAM (p, version);

    /* Add in type and length fields */
    *p_buff = (UINT8) ((DATA_ELE_SEQ_DESC_TYPE << 3) | SIZE_IN_NEXT_BYTE);
    *(p_buff + 1) = (UINT8) (p - (p_buff + 2));

    result = SDP_AddAttribute (handle, ATTR_ID_BT_PROFILE_DESC_LIST, DATA_ELE_SEQ_DESC_TYPE, (UINT32) (p - p_buff), p_buff);
    osi_free(p_buff);
    return result;

#else   /* SDP_SERVER_ENABLED == FALSE */
    return (FALSE);
#endif
}