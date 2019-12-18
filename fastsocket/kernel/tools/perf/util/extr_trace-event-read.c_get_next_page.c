#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ off_t ;
struct TYPE_2__ {scalar_t__ size; scalar_t__ offset; int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_1__* cpu_data ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_fd ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mmap (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ page_size ; 
 scalar_t__ read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ read_page ; 
 int /*<<< orphan*/  update_cpu_data_index (int) ; 

__attribute__((used)) static void get_next_page(int cpu)
{
	off_t save_seek;
	off_t ret;

	if (!cpu_data[cpu].page)
		return;

	if (read_page) {
		if (cpu_data[cpu].size <= page_size) {
			free(cpu_data[cpu].page);
			cpu_data[cpu].page = NULL;
			return;
		}

		update_cpu_data_index(cpu);

		/* other parts of the code may expect the pointer to not move */
		save_seek = lseek(input_fd, 0, SEEK_CUR);

		ret = lseek(input_fd, cpu_data[cpu].offset, SEEK_SET);
		if (ret == (off_t)-1)
			die("failed to lseek");
		ret = read(input_fd, cpu_data[cpu].page, page_size);
		if (ret < 0)
			die("failed to read page");

		/* reset the file pointer back */
		lseek(input_fd, save_seek, SEEK_SET);

		return;
	}

	munmap(cpu_data[cpu].page, page_size);
	cpu_data[cpu].page = NULL;

	if (cpu_data[cpu].size <= page_size)
		return;

	update_cpu_data_index(cpu);

	cpu_data[cpu].page = mmap(NULL, page_size, PROT_READ, MAP_PRIVATE,
				  input_fd, cpu_data[cpu].offset);
	if (cpu_data[cpu].page == MAP_FAILED)
		die("failed to mmap cpu %d at offset 0x%llx",
		    cpu, cpu_data[cpu].offset);
}