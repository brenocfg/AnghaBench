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
struct fdt_reserve_entry {void* size; void* address; } ;
struct data {int dummy; } ;
typedef  int /*<<< orphan*/  bere ;

/* Variables and functions */
 void* cpu_to_fdt64 (void*) ; 
 struct data data_append_data (struct data,struct fdt_reserve_entry*,int) ; 

struct data data_append_re(struct data d, const struct fdt_reserve_entry *re)
{
	struct fdt_reserve_entry bere;

	bere.address = cpu_to_fdt64(re->address);
	bere.size = cpu_to_fdt64(re->size);

	return data_append_data(d, &bere, sizeof(bere));
}