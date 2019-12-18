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
typedef  int UINT16 ;

/* Variables and functions */
 int /*<<< orphan*/  BE_STREAM_TO_UINT16 (int,int*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT32 (int,int*) ; 
 int /*<<< orphan*/  BE_STREAM_TO_UINT8 (int,int*) ; 
#define  SIZE_EIGHT_BYTES 135 
#define  SIZE_FOUR_BYTES 134 
#define  SIZE_IN_NEXT_BYTE 133 
#define  SIZE_IN_NEXT_LONG 132 
#define  SIZE_IN_NEXT_WORD 131 
#define  SIZE_ONE_BYTE 130 
#define  SIZE_SIXTEEN_BYTES 129 
#define  SIZE_TWO_BYTES 128 

UINT8 *sdpu_get_len_from_type (UINT8 *p, UINT8 type, UINT32 *p_len)
{
    UINT8   u8;
    UINT16  u16;
    UINT32  u32;

    switch (type & 7) {
    case SIZE_ONE_BYTE:
        *p_len = 1;
        break;
    case SIZE_TWO_BYTES:
        *p_len = 2;
        break;
    case SIZE_FOUR_BYTES:
        *p_len = 4;
        break;
    case SIZE_EIGHT_BYTES:
        *p_len = 8;
        break;
    case SIZE_SIXTEEN_BYTES:
        *p_len = 16;
        break;
    case SIZE_IN_NEXT_BYTE:
        BE_STREAM_TO_UINT8 (u8, p);
        *p_len = u8;
        break;
    case SIZE_IN_NEXT_WORD:
        BE_STREAM_TO_UINT16 (u16, p);
        *p_len = u16;
        break;
    case SIZE_IN_NEXT_LONG:
        BE_STREAM_TO_UINT32 (u32, p);
        *p_len = (UINT16) u32;
        break;
    }

    return (p);
}