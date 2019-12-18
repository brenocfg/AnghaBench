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

__attribute__((used)) static uint32 make_lut_bg_ste(uint32 bx, uint32 ax)
{
  int bf = (bx & 0x7F);
  int bp = (bx & 0x40);
  int b  = (bx & 0x0F);
  
  int af = (ax & 0x7F);   
  int ap = (ax & 0x40);
  int a  = (ax & 0x0F);

  int c = (ap ? (a ? af : bf) : (bp ? (b ? bf : af) : (a ? af : bf)));

  /* Half intensity when both pixels are low priority */
  c |= ((ap | bp) << 1);

  /* Strip palette & priority bits from transparent pixels */
  if((c & 0x0F) == 0x00) c &= 0x80;

  return (c);
}