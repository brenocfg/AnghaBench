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
struct amd64_pvt {scalar_t__ ext_model; int dclr0; scalar_t__ dclr1; } ;

/* Variables and functions */
 scalar_t__ K8_REV_F ; 
 int REVE_WIDTH_128 ; 
 int WIDTH_128 ; 

__attribute__((used)) static int k8_early_channel_count(struct amd64_pvt *pvt)
{
	int flag;

	if (pvt->ext_model >= K8_REV_F)
		/* RevF (NPT) and later */
		flag = pvt->dclr0 & WIDTH_128;
	else
		/* RevE and earlier */
		flag = pvt->dclr0 & REVE_WIDTH_128;

	/* not used */
	pvt->dclr1 = 0;

	return (flag) ? 2 : 1;
}