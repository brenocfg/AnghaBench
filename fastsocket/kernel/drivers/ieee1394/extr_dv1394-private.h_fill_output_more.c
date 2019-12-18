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
struct output_more {void** q; } ;

/* Variables and functions */
 void* cpu_to_le32 (unsigned long) ; 

__attribute__((used)) static inline void fill_output_more(struct output_more *om,
				    unsigned int data_size,
				    unsigned long data_phys_addr)
{
	om->q[0] = cpu_to_le32(data_size);
	om->q[1] = cpu_to_le32(data_phys_addr);
	om->q[2] = cpu_to_le32(0);
	om->q[3] = cpu_to_le32(0);
}