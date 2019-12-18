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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  prop; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  int /*<<< orphan*/  CLzmaProps ;
typedef  TYPE_1__ CLzmaDec ;

/* Variables and functions */
 int /*<<< orphan*/  LzmaDec_AllocateProbs2 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaProps_Decode (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 

SRes LzmaDec_AllocateProbs(CLzmaDec *p, const uint8_t *props, unsigned propsSize, ISzAlloc *alloc)
{
   CLzmaProps propNew;
   RINOK(LzmaProps_Decode(&propNew, props, propsSize));
   RINOK(LzmaDec_AllocateProbs2(p, &propNew, alloc));
   p->prop = propNew;
   return SZ_OK;
}