#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32 ;

/* Variables and functions */

__attribute__((used)) static uint32 make_lut_obj(uint32 bx, uint32 sx)
{
  int c;

  int bf = (bx & 0x7F);
  int bs = (bx & 0x80);
  int sf = (sx & 0x7F);

  if((sx & 0x0F) == 0) return bx;

  c = (bs ? bf : sf);

  /* Strip palette bits from transparent pixels */
  if((c & 0x0F) == 0x00) c &= 0xC0;

  return (c | 0x80);
}