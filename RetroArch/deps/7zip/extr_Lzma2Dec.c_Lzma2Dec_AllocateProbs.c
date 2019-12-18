#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  decoder; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ISzAlloc ;
typedef  TYPE_1__ CLzma2Dec ;

/* Variables and functions */
 int LZMA_PROPS_SIZE ; 
 int /*<<< orphan*/  Lzma2Dec_GetOldProps (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LzmaDec_AllocateProbs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 

SRes Lzma2Dec_AllocateProbs(CLzma2Dec *p, uint8_t prop, ISzAlloc *alloc)
{
   uint8_t props[LZMA_PROPS_SIZE];
   RINOK(Lzma2Dec_GetOldProps(prop, props));
   return LzmaDec_AllocateProbs(&p->decoder, props, LZMA_PROPS_SIZE, alloc);
}