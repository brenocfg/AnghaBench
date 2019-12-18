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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_3__ {int /*<<< orphan*/  userData; scalar_t__ (* realloc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ;} ;
typedef  TYPE_1__ JSON_MemorySuite ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static byte* DoubleBuffer(const JSON_MemorySuite* pMemorySuite, byte* pDefaultBuffer, byte* pBuffer, size_t length)
{
   size_t newLength = length * 2;
   if (newLength < length)
   {
      pBuffer = NULL;
   }
   else if (pBuffer == pDefaultBuffer)
   {
      pBuffer = (byte*)pMemorySuite->realloc(pMemorySuite->userData, NULL, newLength);
      if (pBuffer)
      {
         memcpy(pBuffer, pDefaultBuffer, length);
      }
   }
   else
   {
      pBuffer = (byte*)pMemorySuite->realloc(pMemorySuite->userData, pBuffer, newLength);
   }
   return pBuffer;
}