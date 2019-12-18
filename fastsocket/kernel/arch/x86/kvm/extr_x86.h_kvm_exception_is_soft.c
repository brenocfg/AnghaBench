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
 unsigned int BP_VECTOR ; 
 unsigned int OF_VECTOR ; 

__attribute__((used)) static inline bool kvm_exception_is_soft(unsigned int nr)
{
	return (nr == BP_VECTOR) || (nr == OF_VECTOR);
}