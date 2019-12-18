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
typedef  int /*<<< orphan*/  HUFv06_DEltX4 ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BITv06_DStream_t ;

/* Variables and functions */
 int /*<<< orphan*/  BITv06_endOfDStream (int /*<<< orphan*/ *) ; 
 size_t BITv06_initDStream (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,size_t) ; 
 size_t ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HUFv06_decodeStreamX4 (int /*<<< orphan*/ * const,int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int /*<<< orphan*/  const) ; 
 scalar_t__ HUFv06_isError (size_t const) ; 
 int /*<<< orphan*/  corruption_detected ; 

size_t HUFv06_decompress1X4_usingDTable(
          void* dst,  size_t dstSize,
    const void* cSrc, size_t cSrcSize,
    const U32* DTable)
{
    const BYTE* const istart = (const BYTE*) cSrc;
    BYTE* const ostart = (BYTE*) dst;
    BYTE* const oend = ostart + dstSize;

    const U32 dtLog = DTable[0];
    const void* const dtPtr = DTable;
    const HUFv06_DEltX4* const dt = ((const HUFv06_DEltX4*)dtPtr) +1;

    /* Init */
    BITv06_DStream_t bitD;
    { size_t const errorCode = BITv06_initDStream(&bitD, istart, cSrcSize);
      if (HUFv06_isError(errorCode)) return errorCode; }

    /* decode */
    HUFv06_decodeStreamX4(ostart, &bitD, oend, dt, dtLog);

    /* check */
    if (!BITv06_endOfDStream(&bitD)) return ERROR(corruption_detected);

    /* decoded size */
    return dstSize;
}