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
struct aic7xxx_host {int chip; } ;

/* Variables and functions */
 int AHC_AIC7895 ; 
 int AHC_CHIPID_MASK ; 

__attribute__((used)) static int
aic7xxx_patch9_func(struct aic7xxx_host *p)
{
	return ((p->chip & AHC_CHIPID_MASK) == AHC_AIC7895);
}