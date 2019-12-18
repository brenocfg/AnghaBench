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

__attribute__((used)) static inline unsigned int
make_scp_header(unsigned int target_id, unsigned int source_id,
		unsigned int get_flag, unsigned int req,
		unsigned int device_flag, unsigned int resp_flag,
		unsigned int error_flag, unsigned int data_size)
{
	unsigned int header = 0;

	header = (data_size & 0x1f) << 27;
	header |= (error_flag & 0x01) << 26;
	header |= (resp_flag & 0x01) << 25;
	header |= (device_flag & 0x01) << 24;
	header |= (req & 0x7f) << 17;
	header |= (get_flag & 0x01) << 16;
	header |= (source_id & 0xff) << 8;
	header |= target_id & 0xff;

	return header;
}