#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int* crc; int /*<<< orphan*/ * hash; scalar_t__ directInput; int /*<<< orphan*/ * bufferBase; } ;
typedef  TYPE_1__ CMatchFinder ;

/* Variables and functions */
 int /*<<< orphan*/  MatchFinder_SetDefaultSettings (TYPE_1__*) ; 
 int kCrcPoly ; 

void MatchFinder_Construct(CMatchFinder *p)
{
  uint32_t i;
  p->bufferBase = NULL;
  p->directInput = 0;
  p->hash = NULL;
  MatchFinder_SetDefaultSettings(p);

  for (i = 0; i < 256; i++)
  {
    uint32_t r = i;
    unsigned j;
    for (j = 0; j < 8; j++)
      r = (r >> 1) ^ (kCrcPoly & ~((r & 1) - 1));
    p->crc[i] = r;
  }
}