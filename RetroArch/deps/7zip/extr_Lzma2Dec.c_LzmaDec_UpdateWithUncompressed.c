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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
struct TYPE_4__ {size_t dicSize; } ;
struct TYPE_5__ {scalar_t__ checkDicSize; size_t processedPos; TYPE_1__ prop; scalar_t__ dicPos; scalar_t__ dic; } ;
typedef  TYPE_2__ CLzmaDec ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void LzmaDec_UpdateWithUncompressed(CLzmaDec *p, const uint8_t *src, size_t size)
{
   memcpy(p->dic + p->dicPos, src, size);
   p->dicPos += size;
   if (p->checkDicSize == 0 && p->prop.dicSize - p->processedPos <= size)
      p->checkDicSize = p->prop.dicSize;
   p->processedPos += (uint32_t)size;
}