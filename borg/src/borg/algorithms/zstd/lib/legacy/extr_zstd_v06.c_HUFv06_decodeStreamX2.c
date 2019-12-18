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
typedef  int /*<<< orphan*/  U32 ;
typedef  int /*<<< orphan*/  HUFv06_DEltX2 ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITv06_DStream_t ;

/* Variables and functions */
 scalar_t__ BITv06_DStream_unfinished ; 
 scalar_t__ BITv06_reloadDStream (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  HUFv06_DECODE_SYMBOLX2_0 (int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  HUFv06_DECODE_SYMBOLX2_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  HUFv06_DECODE_SYMBOLX2_2 (int /*<<< orphan*/ *,int /*<<< orphan*/ * const) ; 

__attribute__((used)) static inline size_t HUFv06_decodeStreamX2(BYTE* p, BITv06_DStream_t* const bitDPtr, BYTE* const pEnd, const HUFv06_DEltX2* const dt, const U32 dtLog)
{
    BYTE* const pStart = p;

    /* up to 4 symbols at a time */
    while ((BITv06_reloadDStream(bitDPtr) == BITv06_DStream_unfinished) && (p <= pEnd-4)) {
        HUFv06_DECODE_SYMBOLX2_2(p, bitDPtr);
        HUFv06_DECODE_SYMBOLX2_1(p, bitDPtr);
        HUFv06_DECODE_SYMBOLX2_2(p, bitDPtr);
        HUFv06_DECODE_SYMBOLX2_0(p, bitDPtr);
    }

    /* closer to the end */
    while ((BITv06_reloadDStream(bitDPtr) == BITv06_DStream_unfinished) && (p < pEnd))
        HUFv06_DECODE_SYMBOLX2_0(p, bitDPtr);

    /* no more data to retrieve from bitstream, hence no need to reload */
    while (p < pEnd)
        HUFv06_DECODE_SYMBOLX2_0(p, bitDPtr);

    return pEnd-pStart;
}