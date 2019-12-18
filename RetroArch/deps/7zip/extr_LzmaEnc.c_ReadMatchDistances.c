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
typedef  int uint32_t ;
typedef  size_t ptrdiff_t ;
struct TYPE_4__ {int (* GetNumAvailableBytes ) (int /*<<< orphan*/ ) ;int (* GetMatches ) (int /*<<< orphan*/ ,int*) ;unsigned char* (* GetPointerToCurrentPos ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int numAvail; int* matches; int numFastBytes; int /*<<< orphan*/  additionalOffset; int /*<<< orphan*/  matchFinderObj; TYPE_1__ matchFinder; } ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 int LZMA_MATCH_LEN_MAX ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int*) ; 
 unsigned char* stub3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t ReadMatchDistances(CLzmaEnc *p, uint32_t *numDistancePairsRes)
{
  uint32_t lenRes = 0, numPairs;
  p->numAvail = p->matchFinder.GetNumAvailableBytes(p->matchFinderObj);
  numPairs = p->matchFinder.GetMatches(p->matchFinderObj, p->matches);

  if (numPairs > 0)
  {
    lenRes = p->matches[numPairs - 2];
    if (lenRes == p->numFastBytes)
    {
      uint32_t numAvail = p->numAvail;
      if (numAvail > LZMA_MATCH_LEN_MAX)
        numAvail = LZMA_MATCH_LEN_MAX;
      {
        const unsigned char *pbyCur = p->matchFinder.GetPointerToCurrentPos(p->matchFinderObj) - 1;
        const unsigned char *pby = pbyCur + lenRes;
        ptrdiff_t dif = (ptrdiff_t)-1 - p->matches[numPairs - 1];
        const unsigned char *pbyLim = pbyCur + numAvail;
        for (; pby != pbyLim && *pby == pby[dif]; pby++);
        lenRes = (uint32_t)(pby - pbyCur);
      }
    }
  }
  p->additionalOffset++;
  *numDistancePairsRes = numPairs;
  return lenRes;
}