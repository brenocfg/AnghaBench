#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t num_uids; TYPE_1__* uuid_entry; } ;
typedef  TYPE_2__ tSDP_UUID_SEQ ;
typedef  int UINT8 ;
typedef  scalar_t__ UINT32 ;
typedef  scalar_t__ UINT16 ;
struct TYPE_4__ {int /*<<< orphan*/  value; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BE_STREAM_TO_ARRAY (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT16 (scalar_t__,int*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT32 (scalar_t__,int*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT8 (scalar_t__,int*) ; 
 int DATA_ELE_SEQ_DESC_TYPE ; 
 size_t MAX_UUIDS_PER_SEQ ; 
#define  SIZE_FOUR_BYTES 133 
#define  SIZE_IN_NEXT_BYTE 132 
#define  SIZE_IN_NEXT_LONG 131 
#define  SIZE_IN_NEXT_WORD 130 
#define  SIZE_SIXTEEN_BYTES 129 
#define  SIZE_TWO_BYTES 128 
 int UUID_DESC_TYPE ; 

UINT8 *sdpu_extract_uid_seq (UINT8 *p, UINT16 param_len, tSDP_UUID_SEQ *p_seq)
{
    UINT8   *p_seq_end;
    UINT8   descr, type, size;
    UINT32  seq_len, uuid_len;

    /* Assume none found */
    p_seq->num_uids = 0;

    /* A UID sequence is composed of a bunch of UIDs. */

    BE_STREAM_TO_UINT8 (descr, p);
    type = descr >> 3;
    size = descr & 7;

    if (type != DATA_ELE_SEQ_DESC_TYPE) {
        return (NULL);
    }

    switch (size) {
    case SIZE_TWO_BYTES:
        seq_len = 2;
        break;
    case SIZE_FOUR_BYTES:
        seq_len = 4;
        break;
    case SIZE_SIXTEEN_BYTES:
        seq_len = 16;
        break;
    case SIZE_IN_NEXT_BYTE:
        BE_STREAM_TO_UINT8 (seq_len, p);
        break;
    case SIZE_IN_NEXT_WORD:
        BE_STREAM_TO_UINT16 (seq_len, p);
        break;
    case SIZE_IN_NEXT_LONG:
        BE_STREAM_TO_UINT32 (seq_len, p);
        break;
    default:
        return (NULL);
    }

    if (seq_len >= param_len) {
        return (NULL);
    }

    p_seq_end = p + seq_len;

    /* Loop through, extracting the UIDs */
    for ( ; p < p_seq_end ; ) {
        BE_STREAM_TO_UINT8 (descr, p);
        type = descr >> 3;
        size = descr & 7;

        if (type != UUID_DESC_TYPE) {
            return (NULL);
        }

        switch (size) {
        case SIZE_TWO_BYTES:
            uuid_len = 2;
            break;
        case SIZE_FOUR_BYTES:
            uuid_len = 4;
            break;
        case SIZE_SIXTEEN_BYTES:
            uuid_len = 16;
            break;
        case SIZE_IN_NEXT_BYTE:
            BE_STREAM_TO_UINT8 (uuid_len, p);
            break;
        case SIZE_IN_NEXT_WORD:
            BE_STREAM_TO_UINT16 (uuid_len, p);
            break;
        case SIZE_IN_NEXT_LONG:
            BE_STREAM_TO_UINT32 (uuid_len, p);
            break;
        default:
            return (NULL);
        }

        /* If UUID length is valid, copy it across */
        if ((uuid_len == 2) || (uuid_len == 4) || (uuid_len == 16)) {
            p_seq->uuid_entry[p_seq->num_uids].len = (UINT16) uuid_len;
            BE_STREAM_TO_ARRAY (p, p_seq->uuid_entry[p_seq->num_uids].value, (int)uuid_len);
            p_seq->num_uids++;
        } else {
            return (NULL);
        }

        /* We can only do so many */
        if (p_seq->num_uids >= MAX_UUIDS_PER_SEQ) {
            return (NULL);
        }
    }

    if (p != p_seq_end) {
        return (NULL);
    }

    return (p);
}