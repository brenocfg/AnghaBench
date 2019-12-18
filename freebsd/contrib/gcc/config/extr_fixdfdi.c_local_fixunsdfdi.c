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
typedef  int USItype ;
typedef  int UDItype ;
typedef  int DItype ;
typedef  int DFtype ;

/* Variables and functions */

__attribute__((used)) static DItype
local_fixunsdfdi (DFtype a)
{
  USItype hi, lo;

  hi = a / (((UDItype) 1) << (sizeof (USItype) * 8));
  lo = a - ((DFtype) hi) * (((UDItype) 1) << (sizeof (USItype) * 8));
  return ((UDItype) hi << (sizeof (USItype) * 8)) | lo;
}