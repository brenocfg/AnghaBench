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
struct input_more {void** q; } ;

/* Variables and functions */
 void* cpu_to_le32 (unsigned long) ; 

__attribute__((used)) static inline void fill_input_more(struct input_more *im,
				   int want_interrupt,
				   unsigned int data_size,
				   unsigned long data_phys_addr)
{
	u32 temp =  2 << 28; /* INPUT_MORE */
	temp |= 8 << 24; /* s = 1, update xferStatus and resCount */
	if (want_interrupt)
		temp |= 0 << 20; /* interrupts, i=0 in packet-per-buffer mode */
	temp |= 0x0 << 16; /* disable branch to address for packet-per-buffer mode */
	                       /* disable wait on sync field, not used in DV :-( */
       	temp |= data_size;

	im->q[0] = cpu_to_le32(temp);
	im->q[1] = cpu_to_le32(data_phys_addr);
	im->q[2] = cpu_to_le32(0); /* branchAddress and Z not use in packet-per-buffer mode */
	im->q[3] = cpu_to_le32(0); /* xferStatus & resCount, resCount must be initialize to data_size */
}