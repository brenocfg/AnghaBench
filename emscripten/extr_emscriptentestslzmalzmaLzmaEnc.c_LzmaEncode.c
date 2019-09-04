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
typedef  int /*<<< orphan*/  SizeT ;
typedef  scalar_t__ SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  int /*<<< orphan*/  ICompressProgress ;
typedef  int /*<<< orphan*/  CLzmaEncProps ;
typedef  int /*<<< orphan*/  CLzmaEnc ;
typedef  int /*<<< orphan*/  Byte ;

/* Variables and functions */
 scalar_t__ LzmaEnc_Create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaEnc_Destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LzmaEnc_MemEncode (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ LzmaEnc_SetProps (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ LzmaEnc_WriteProperties (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SZ_ERROR_MEM ; 
 scalar_t__ SZ_OK ; 

SRes LzmaEncode(Byte *dest, SizeT *destLen, const Byte *src, SizeT srcLen,
    const CLzmaEncProps *props, Byte *propsEncoded, SizeT *propsSize, int writeEndMark,
    ICompressProgress *progress, ISzAlloc *alloc, ISzAlloc *allocBig)
{
  CLzmaEnc *p = (CLzmaEnc *)LzmaEnc_Create(alloc);
  SRes res;
  if (p == 0)
    return SZ_ERROR_MEM;

  res = LzmaEnc_SetProps(p, props);
  if (res == SZ_OK)
  {
    res = LzmaEnc_WriteProperties(p, propsEncoded, propsSize);
    if (res == SZ_OK)
      res = LzmaEnc_MemEncode(p, dest, destLen, src, srcLen,
          writeEndMark, progress, alloc, allocBig);
  }

  LzmaEnc_Destroy(p, alloc, allocBig);
  return res;
}