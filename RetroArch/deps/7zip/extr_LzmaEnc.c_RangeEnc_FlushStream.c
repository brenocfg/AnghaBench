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
struct TYPE_5__ {size_t (* Write ) (TYPE_2__*,size_t,size_t) ;} ;
struct TYPE_4__ {scalar_t__ res; size_t buf; size_t bufBase; size_t processed; TYPE_2__* outStream; } ;
typedef  TYPE_1__ CRangeEnc ;

/* Variables and functions */
 scalar_t__ SZ_ERROR_WRITE ; 
 scalar_t__ SZ_OK ; 
 size_t stub1 (TYPE_2__*,size_t,size_t) ; 

__attribute__((used)) static void RangeEnc_FlushStream(CRangeEnc *p)
{
  size_t num;
  if (p->res != SZ_OK)
    return;
  num = p->buf - p->bufBase;
  if (num != p->outStream->Write(p->outStream, p->bufBase, num))
    p->res = SZ_ERROR_WRITE;
  p->processed += num;
  p->buf = p->bufBase;
}