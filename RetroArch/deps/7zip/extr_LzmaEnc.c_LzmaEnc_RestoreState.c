#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  litProbs; int /*<<< orphan*/  reps; int /*<<< orphan*/  posAlignEncoder; int /*<<< orphan*/  posEncoders; int /*<<< orphan*/  isRepG2; int /*<<< orphan*/  isRepG1; int /*<<< orphan*/  isRepG0; int /*<<< orphan*/  isRep; int /*<<< orphan*/ * posSlotEncoder; int /*<<< orphan*/ * isRep0Long; int /*<<< orphan*/ * isMatch; int /*<<< orphan*/  state; int /*<<< orphan*/  repLenEnc; int /*<<< orphan*/  lenEnc; } ;
struct TYPE_4__ {int lclp; int /*<<< orphan*/  litProbs; int /*<<< orphan*/  reps; int /*<<< orphan*/  posAlignEncoder; int /*<<< orphan*/  posEncoders; int /*<<< orphan*/  isRepG2; int /*<<< orphan*/  isRepG1; int /*<<< orphan*/  isRepG0; int /*<<< orphan*/  isRep; int /*<<< orphan*/ * posSlotEncoder; int /*<<< orphan*/ * isRep0Long; int /*<<< orphan*/ * isMatch; int /*<<< orphan*/  state; int /*<<< orphan*/  repLenEnc; int /*<<< orphan*/  lenEnc; TYPE_1__ saveState; } ;
typedef  TYPE_1__ CSaveState ;
typedef  int /*<<< orphan*/  CLzmaProb ;
typedef  scalar_t__ CLzmaEncHandle ;
typedef  TYPE_2__ CLzmaEnc ;

/* Variables and functions */
 int kNumLenToPosStates ; 
 int kNumStates ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void LzmaEnc_RestoreState(CLzmaEncHandle pp)
{
  CLzmaEnc *dest = (CLzmaEnc *)pp;
  const CSaveState *p = &dest->saveState;
  int i;
  dest->lenEnc = p->lenEnc;
  dest->repLenEnc = p->repLenEnc;
  dest->state = p->state;

  for (i = 0; i < kNumStates; i++)
  {
    memcpy(dest->isMatch[i], p->isMatch[i], sizeof(p->isMatch[i]));
    memcpy(dest->isRep0Long[i], p->isRep0Long[i], sizeof(p->isRep0Long[i]));
  }
  for (i = 0; i < kNumLenToPosStates; i++)
    memcpy(dest->posSlotEncoder[i], p->posSlotEncoder[i], sizeof(p->posSlotEncoder[i]));
  memcpy(dest->isRep, p->isRep, sizeof(p->isRep));
  memcpy(dest->isRepG0, p->isRepG0, sizeof(p->isRepG0));
  memcpy(dest->isRepG1, p->isRepG1, sizeof(p->isRepG1));
  memcpy(dest->isRepG2, p->isRepG2, sizeof(p->isRepG2));
  memcpy(dest->posEncoders, p->posEncoders, sizeof(p->posEncoders));
  memcpy(dest->posAlignEncoder, p->posAlignEncoder, sizeof(p->posAlignEncoder));
  memcpy(dest->reps, p->reps, sizeof(p->reps));
  memcpy(dest->litProbs, p->litProbs, ((uint32_t)0x300 << dest->lclp) * sizeof(CLzmaProb));
}