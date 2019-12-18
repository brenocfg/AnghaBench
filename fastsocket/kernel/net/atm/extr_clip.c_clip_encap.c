#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct atm_vcc {int dummy; } ;
struct TYPE_2__ {int encap; } ;

/* Variables and functions */
 TYPE_1__* CLIP_VCC (struct atm_vcc*) ; 

__attribute__((used)) static int clip_encap(struct atm_vcc *vcc, int mode)
{
	CLIP_VCC(vcc)->encap = mode;
	return 0;
}