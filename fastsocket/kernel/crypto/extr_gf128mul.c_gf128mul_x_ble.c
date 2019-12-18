#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_4__ {void* b; void* a; } ;
typedef  TYPE_1__ be128 ;

/* Variables and functions */
 void* cpu_to_le64 (int) ; 
 int* gf128mul_table_bbe ; 
 int le64_to_cpu (void*) ; 

void gf128mul_x_ble(be128 *r, const be128 *x)
{
	u64 a = le64_to_cpu(x->a);
	u64 b = le64_to_cpu(x->b);
	u64 _tt = gf128mul_table_bbe[b >> 63];

	r->a = cpu_to_le64((a << 1) ^ _tt);
	r->b = cpu_to_le64((b << 1) | (a >> 63));
}