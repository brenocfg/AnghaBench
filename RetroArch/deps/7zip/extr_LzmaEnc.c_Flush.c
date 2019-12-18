#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {int finished; int pbMask; int /*<<< orphan*/  rc; scalar_t__ writeEndMark; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CLzmaEnc ;

/* Variables and functions */
 int /*<<< orphan*/  CheckErrors (TYPE_1__*) ; 
 int /*<<< orphan*/  RangeEnc_FlushData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RangeEnc_FlushStream (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteEndMarker (TYPE_1__*,int) ; 

__attribute__((used)) static SRes Flush(CLzmaEnc *p, uint32_t nowPos)
{
  /* ReleaseMFStream(); */
  p->finished = true;
  if (p->writeEndMark)
    WriteEndMarker(p, nowPos & p->pbMask);
  RangeEnc_FlushData(&p->rc);
  RangeEnc_FlushStream(&p->rc);
  return CheckErrors(p);
}