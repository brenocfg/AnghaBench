#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {int keepSizeBefore; int keepSizeAfter; int matchMaxLen; int numHashBytes; int hashMask; int historySize; int hashSizeSum; int cyclicBufferSize; size_t numRefs; int /*<<< orphan*/  hash; scalar_t__ son; scalar_t__ btMode; scalar_t__ fixedHashSize; } ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_1__ CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  AllocRefs (size_t,int /*<<< orphan*/ *) ; 
 int LzFindkMaxHistorySize ; 
 scalar_t__ LzInWindow_Create (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MatchFinder_Free (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MatchFinder_FreeThisClassMemory (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ kHash2Size ; 
 scalar_t__ kHash3Size ; 
 scalar_t__ kHash4Size ; 

int MatchFinder_Create(CMatchFinder *p, uint32_t historySize,
    uint32_t keepAddBufferBefore, uint32_t matchMaxLen, uint32_t keepAddBufferAfter,
    ISzAlloc *alloc)
{
  uint32_t sizeReserv;

  if (historySize > LzFindkMaxHistorySize)
  {
    MatchFinder_Free(p, alloc);
    return 0;
  }

  sizeReserv = historySize >> 1;
       if (historySize >= ((uint32_t)3 << 30)) sizeReserv = historySize >> 3;
  else if (historySize >= ((uint32_t)2 << 30)) sizeReserv = historySize >> 2;

  sizeReserv += (keepAddBufferBefore + matchMaxLen + keepAddBufferAfter) / 2 + (1 << 19);

  p->keepSizeBefore = historySize + keepAddBufferBefore + 1;
  p->keepSizeAfter = matchMaxLen + keepAddBufferAfter;

  /* we need one additional byte, since we use MoveBlock after pos++ and before dictionary using */

  if (LzInWindow_Create(p, sizeReserv, alloc))
  {
    uint32_t newCyclicBufferSize = historySize + 1;
    uint32_t hs;
    p->matchMaxLen = matchMaxLen;
    {
      p->fixedHashSize = 0;
      if (p->numHashBytes == 2)
        hs = (1 << 16) - 1;
      else
      {
        hs = historySize - 1;
        hs |= (hs >> 1);
        hs |= (hs >> 2);
        hs |= (hs >> 4);
        hs |= (hs >> 8);
        hs >>= 1;
        hs |= 0xFFFF; /* don't change it! It's required for Deflate */
        if (hs > (1 << 24))
        {
          if (p->numHashBytes == 3)
            hs = (1 << 24) - 1;
          else
            hs >>= 1;
          /* if (bigHash) mode, GetHeads4b() in LzFindMt.c needs (hs >= ((1 << 24) - 1))) */
        }
      }
      p->hashMask = hs;
      hs++;
      if (p->numHashBytes > 2) p->fixedHashSize += kHash2Size;
      if (p->numHashBytes > 3) p->fixedHashSize += kHash3Size;
      if (p->numHashBytes > 4) p->fixedHashSize += kHash4Size;
      hs += p->fixedHashSize;
    }

    {
      size_t newSize;
      size_t numSons;
      p->historySize = historySize;
      p->hashSizeSum = hs;
      p->cyclicBufferSize = newCyclicBufferSize;

      numSons = newCyclicBufferSize;
      if (p->btMode)
        numSons <<= 1;
      newSize = hs + numSons;

      if (p->hash && p->numRefs == newSize)
        return 1;

      MatchFinder_FreeThisClassMemory(p, alloc);
      p->numRefs = newSize;
      p->hash = AllocRefs(newSize, alloc);

      if (p->hash)
      {
        p->son = p->hash + p->hashSizeSum;
        return 1;
      }
    }
  }

  MatchFinder_Free(p, alloc);
  return 0;
}