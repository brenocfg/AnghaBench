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
struct iovec {scalar_t__ iov_len; } ;

/* Variables and functions */

__attribute__((used)) static inline int msg_calc_data_size(struct iovec const *msg_sect, u32 num_sect)
{
	int dsz = 0;
	int i;

	for (i = 0; i < num_sect; i++)
		dsz += msg_sect[i].iov_len;
	return dsz;
}