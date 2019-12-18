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
struct tomoyo_io_buffer {int read_eof; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 unsigned int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 unsigned int tomoyo_allocated_memory_for_elements ; 
 unsigned int tomoyo_allocated_memory_for_savename ; 
 int /*<<< orphan*/  tomoyo_dynamic_memory_size ; 
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*,unsigned int const,...) ; 
 int tomoyo_quota_for_elements ; 
 int tomoyo_quota_for_savename ; 

int tomoyo_read_memory_counter(struct tomoyo_io_buffer *head)
{
	if (!head->read_eof) {
		const unsigned int shared
			= tomoyo_allocated_memory_for_savename;
		const unsigned int private
			= tomoyo_allocated_memory_for_elements;
		const unsigned int dynamic
			= atomic_read(&tomoyo_dynamic_memory_size);
		char buffer[64];

		memset(buffer, 0, sizeof(buffer));
		if (tomoyo_quota_for_savename)
			snprintf(buffer, sizeof(buffer) - 1,
				 "   (Quota: %10u)",
				 tomoyo_quota_for_savename);
		else
			buffer[0] = '\0';
		tomoyo_io_printf(head, "Shared:  %10u%s\n", shared, buffer);
		if (tomoyo_quota_for_elements)
			snprintf(buffer, sizeof(buffer) - 1,
				 "   (Quota: %10u)",
				 tomoyo_quota_for_elements);
		else
			buffer[0] = '\0';
		tomoyo_io_printf(head, "Private: %10u%s\n", private, buffer);
		tomoyo_io_printf(head, "Dynamic: %10u\n", dynamic);
		tomoyo_io_printf(head, "Total:   %10u\n",
				 shared + private + dynamic);
		head->read_eof = true;
	}
	return 0;
}