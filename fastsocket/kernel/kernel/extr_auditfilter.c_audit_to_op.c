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
typedef  size_t u32 ;

/* Variables and functions */
 size_t Audit_bad ; 
 size_t Audit_equal ; 
 size_t* audit_ops ; 

__attribute__((used)) static u32 audit_to_op(u32 op)
{
	u32 n;
	for (n = Audit_equal; n < Audit_bad && audit_ops[n] != op; n++)
		;
	return n;
}