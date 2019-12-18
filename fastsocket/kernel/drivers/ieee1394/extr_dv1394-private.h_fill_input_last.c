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
typedef  int u32 ;
struct input_last {void** q; } ;

/* Variables and functions */
 void* cpu_to_le32 (unsigned int) ; 

__attribute__((used)) static inline void fill_input_last(struct input_last *il,
				    int want_interrupt,
				    unsigned int data_size,
				    unsigned long data_phys_addr)
{
	u32 temp =  3 << 28; /* INPUT_LAST */
	temp |= 8 << 24; /* s = 1, update xferStatus and resCount */
	if (want_interrupt)
		temp |= 3 << 20; /* enable interrupts */
	temp |= 0xC << 16; /* enable branch to address */
	                       /* disable wait on sync field, not used in DV :-( */
	temp |= data_size;

	il->q[0] = cpu_to_le32(temp);
	il->q[1] = cpu_to_le32(data_phys_addr);
	il->q[2] = cpu_to_le32(1); /* branchAddress (filled in later) and Z = 1 descriptor in next block */
	il->q[3] = cpu_to_le32(data_size); /* xferStatus & resCount, resCount must be initialize to data_size */
}