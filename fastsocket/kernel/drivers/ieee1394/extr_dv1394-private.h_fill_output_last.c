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
struct output_last {void** q; } ;

/* Variables and functions */
 void* cpu_to_le32 (unsigned long) ; 

__attribute__((used)) static inline void fill_output_last(struct output_last *ol,
				    int want_timestamp,
				    int want_interrupt,
				    unsigned int data_size,
				    unsigned long data_phys_addr)
{
	u32 temp = 0;
	temp |= 1 << 28; /* OUTPUT_LAST */

	if (want_timestamp) /* controller will update timestamp at DMA time */
		temp |= 1 << 27;

	if (want_interrupt)
		temp |= 3 << 20;

	temp |= 3 << 18; /* must take branch */
	temp |= data_size;

	ol->q[0] = cpu_to_le32(temp);
	ol->q[1] = cpu_to_le32(data_phys_addr);
	ol->q[2] = cpu_to_le32(0);
	ol->q[3] = cpu_to_le32(0);
}