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

__attribute__((used)) static uint32 make_lut_bgobj(uint32 bx, uint32 sx)
{
  int c;

  int bf = (bx & 0x3F);
  int bs = (bx & 0x80);
  int bp = (bx & 0x40);
  int b  = (bx & 0x0F);
  
  int sf = (sx & 0x3F);
  int sp = (sx & 0x40);
  int s  = (sx & 0x0F);

  if(s == 0) return bx;

  /* Previous sprite has higher priority */
  if(bs) return bx;

  c = (sp ? sf : (bp ? (b ? bf : sf) : sf));

  /* Strip palette & priority bits from transparent pixels */
  if((c & 0x0F) == 0x00) c &= 0x80;

  return (c | 0x80);
}