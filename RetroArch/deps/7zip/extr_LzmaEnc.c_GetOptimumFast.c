#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_6__ {unsigned char* (* GetPointerToCurrentPos ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {scalar_t__ additionalOffset; int longestMatchLength; int numPairs; int numAvail; unsigned char const** reps; int numFastBytes; int* matches; int /*<<< orphan*/  matchFinderObj; TYPE_1__ matchFinder; } ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 scalar_t__ ChangePair (int const,int) ; 
 int LZMA_MATCH_LEN_MAX ; 
 int LZMA_NUM_REPS ; 
 int /*<<< orphan*/  MovePos (TYPE_2__*,int) ; 
 void* ReadMatchDistances (TYPE_2__*,int*) ; 
 unsigned char* stub1 (int /*<<< orphan*/ ) ; 
 unsigned char* stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t GetOptimumFast(CLzmaEnc *p, uint32_t *backRes)
{
  uint32_t numAvail, mainLen, mainDist, numPairs, repIndex, repLen, i;
  const unsigned char *data;
  const uint32_t *matches;

  if (p->additionalOffset == 0)
    mainLen = ReadMatchDistances(p, &numPairs);
  else
  {
    mainLen = p->longestMatchLength;
    numPairs = p->numPairs;
  }

  numAvail = p->numAvail;
  *backRes = (uint32_t)-1;
  if (numAvail < 2)
    return 1;
  if (numAvail > LZMA_MATCH_LEN_MAX)
    numAvail = LZMA_MATCH_LEN_MAX;
  data = p->matchFinder.GetPointerToCurrentPos(p->matchFinderObj) - 1;

  repLen = repIndex = 0;
  for (i = 0; i < LZMA_NUM_REPS; i++)
  {
    uint32_t len;
    const unsigned char *data2 = data - p->reps[i] - 1;
    if (data[0] != data2[0] || data[1] != data2[1])
      continue;
    for (len = 2; len < numAvail && data[len] == data2[len]; len++);
    if (len >= p->numFastBytes)
    {
      *backRes = i;
      MovePos(p, len - 1);
      return len;
    }
    if (len > repLen)
    {
      repIndex = i;
      repLen = len;
    }
  }

  matches = p->matches;
  if (mainLen >= p->numFastBytes)
  {
    *backRes = matches[numPairs - 1] + LZMA_NUM_REPS;
    MovePos(p, mainLen - 1);
    return mainLen;
  }

  mainDist = 0; /* for GCC */
  if (mainLen >= 2)
  {
    mainDist = matches[numPairs - 1];
    while (numPairs > 2 && mainLen == matches[numPairs - 4] + 1)
    {
      if (!ChangePair(matches[numPairs - 3], mainDist))
        break;
      numPairs -= 2;
      mainLen = matches[numPairs - 2];
      mainDist = matches[numPairs - 1];
    }
    if (mainLen == 2 && mainDist >= 0x80)
      mainLen = 1;
  }

  if (repLen >= 2 && (
        (repLen + 1 >= mainLen) ||
        (repLen + 2 >= mainLen && mainDist >= (1 << 9)) ||
        (repLen + 3 >= mainLen && mainDist >= (1 << 15))))
  {
    *backRes = repIndex;
    MovePos(p, repLen - 1);
    return repLen;
  }

  if (mainLen < 2 || numAvail <= 2)
    return 1;

  p->longestMatchLength = ReadMatchDistances(p, &p->numPairs);
  if (p->longestMatchLength >= 2)
  {
    uint32_t newDistance = matches[p->numPairs - 1];
    if ((p->longestMatchLength >= mainLen && newDistance < mainDist) ||
        (p->longestMatchLength == mainLen + 1 && !ChangePair(mainDist, newDistance)) ||
        (p->longestMatchLength > mainLen + 1) ||
        (p->longestMatchLength + 1 >= mainLen && mainLen >= 3 && ChangePair(newDistance, mainDist)))
      return 1;
  }

  data = p->matchFinder.GetPointerToCurrentPos(p->matchFinderObj) - 1;
  for (i = 0; i < LZMA_NUM_REPS; i++)
  {
    uint32_t len, limit;
    const unsigned char *data2 = data - p->reps[i] - 1;
    if (data[0] != data2[0] || data[1] != data2[1])
      continue;
    limit = mainLen - 1;
    for (len = 2; len < limit && data[len] == data2[len]; len++);
    if (len >= limit)
      return 1;
  }
  *backRes = mainDist + LZMA_NUM_REPS;
  MovePos(p, mainLen - 2);
  return mainLen;
}