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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int link; } ;
struct dcb_output {TYPE_1__ sorconf; } ;

/* Variables and functions */
 scalar_t__ nv94_sor_soff (struct dcb_output*) ; 

__attribute__((used)) static inline u32
nv94_sor_loff(struct dcb_output *outp)
{
	return nv94_sor_soff(outp) + !(outp->sorconf.link & 1) * 0x80;
}