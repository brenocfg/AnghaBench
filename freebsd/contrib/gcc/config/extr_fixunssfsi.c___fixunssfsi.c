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
typedef  scalar_t__ USItype ;
typedef  scalar_t__ SItype ;
typedef  scalar_t__ SFtype ;

/* Variables and functions */
 scalar_t__ SItype_MIN ; 

USItype
__fixunssfsi (SFtype a)
{
  if (a >= - (SFtype) SItype_MIN)
    return (SItype) (a + SItype_MIN) - SItype_MIN;
  return (SItype) a;
}