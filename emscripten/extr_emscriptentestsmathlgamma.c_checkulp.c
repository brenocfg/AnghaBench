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

/* Variables and functions */
 int RN ; 
 double fabsf (float) ; 

__attribute__((used)) static int checkulp(float d, int r)
{
  // TODO: we only care about >=1.5 ulp errors for now, should be 1.0
  if (r == RN)
    return fabsf(d) < 1.5;
  return 1;
}