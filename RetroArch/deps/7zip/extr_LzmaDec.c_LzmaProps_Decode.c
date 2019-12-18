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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_3__ {int dicSize; int lc; int pb; int lp; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ CLzmaProps ;

/* Variables and functions */
 int LZMA_DIC_MIN ; 
 unsigned int LZMA_PROPS_SIZE ; 
 int /*<<< orphan*/  SZ_ERROR_UNSUPPORTED ; 
 int /*<<< orphan*/  SZ_OK ; 

SRes LzmaProps_Decode(CLzmaProps *p, const uint8_t *data, unsigned size)
{
   uint32_t dicSize;
   uint8_t d;

   if (size < LZMA_PROPS_SIZE)
      return SZ_ERROR_UNSUPPORTED;
   else
      dicSize = data[1] | ((uint32_t)data[2] << 8) | ((uint32_t)data[3] << 16) | ((uint32_t)data[4] << 24);

   if (dicSize < LZMA_DIC_MIN)
      dicSize = LZMA_DIC_MIN;
   p->dicSize = dicSize;

   d = data[0];
   if (d >= (9 * 5 * 5))
      return SZ_ERROR_UNSUPPORTED;

   p->lc = d % 9;
   d /= 9;
   p->pb = d / 5;
   p->lp = d % 5;

   return SZ_OK;
}