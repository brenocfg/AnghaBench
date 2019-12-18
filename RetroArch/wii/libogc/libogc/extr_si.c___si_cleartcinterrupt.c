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
 int SICOMCSR_TCINT ; 
 int* _siReg ; 

__attribute__((used)) static __inline__ void __si_cleartcinterrupt()
{
	_siReg[13] = (_siReg[13]|SICOMCSR_TCINT)&SICOMCSR_TCINT;
}