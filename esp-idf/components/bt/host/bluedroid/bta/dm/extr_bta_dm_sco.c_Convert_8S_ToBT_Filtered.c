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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  SRC_TYPE ;
typedef  int INT32 ;
typedef  int /*<<< orphan*/  INT16 ;

/* Variables and functions */
 int /*<<< orphan*/  APPL_TRACE_DEBUG (char*,int,int,int,int,int) ; 
 int BTA_DM_PCM_OVERLAP_SIZE ; 
 int BTA_DM_PCM_SMPL_RATE_11025 ; 
 int BTA_DM_PCM_SMPL_RATE_22050 ; 
 int BTA_DM_PCM_SMPL_RATE_44100 ; 
 int /*<<< orphan*/  CONVERT_11025_TO_BLUETOOTH (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONVERT_22050_TO_BLUETOOTH (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CONVERT_44100_TO_BLUETOOTH (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SRC_CHANNELS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

INT32 Convert_8S_ToBT_Filtered (UINT8 *pSrc, void *pDst, UINT32 dwSrcSamples,
                                UINT32 dwSrcSps, INT32 *pLastCurPos, UINT8 *pOverlapArea)
{
    INT32             CurrentPos = *pLastCurPos;
    SRC_TYPE        *pIn, *pInEnd;
    SRC_TYPE        *pOv, *pOvEnd;
    INT16           *psBtOut = (INT16 *)pDst;

#if BTA_DM_SCO_DEBUG
    APPL_TRACE_DEBUG("Convert_8S_ToBT_Filtered CurrentPos %d, SRC_TYPE %d, SRC_CHANNELS %d, \
        dwSrcSamples %d,  dwSrcSps %d",  	CurrentPos, sizeof (SRC_TYPE), SRC_CHANNELS, \
                     dwSrcSamples, dwSrcSps);
#endif
    memcpy (pOverlapArea + (BTA_DM_PCM_OVERLAP_SIZE * 2), pSrc, BTA_DM_PCM_OVERLAP_SIZE * 2);

    pOv    = (SRC_TYPE *)(pOverlapArea + BTA_DM_PCM_OVERLAP_SIZE);
    pOvEnd = (SRC_TYPE *)(pOverlapArea + (BTA_DM_PCM_OVERLAP_SIZE * 3));

    pIn     = (SRC_TYPE *)(pSrc + BTA_DM_PCM_OVERLAP_SIZE);
    pInEnd  = (SRC_TYPE *)(pSrc + (dwSrcSamples * SRC_CHANNELS * sizeof (SRC_TYPE)) - BTA_DM_PCM_OVERLAP_SIZE);

    if (dwSrcSps == BTA_DM_PCM_SMPL_RATE_44100) {
        CONVERT_44100_TO_BLUETOOTH(pOv, pOvEnd);
        CONVERT_44100_TO_BLUETOOTH(pIn, pInEnd);
    } else if (dwSrcSps == BTA_DM_PCM_SMPL_RATE_22050) {
        CONVERT_22050_TO_BLUETOOTH(pOv, pOvEnd);
        CONVERT_22050_TO_BLUETOOTH(pIn, pInEnd);
    } else if (dwSrcSps == BTA_DM_PCM_SMPL_RATE_11025) {
        CONVERT_11025_TO_BLUETOOTH(pOv, pOvEnd);
        CONVERT_11025_TO_BLUETOOTH(pIn, pInEnd);
    }

    memcpy (pOverlapArea, pSrc + (dwSrcSamples * SRC_CHANNELS * sizeof (SRC_TYPE)) - \
            (BTA_DM_PCM_OVERLAP_SIZE * 2), BTA_DM_PCM_OVERLAP_SIZE * 2);

    *pLastCurPos = CurrentPos;

    return (psBtOut - (INT16 *)pDst);
}