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
typedef  unsigned int __u32 ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 scalar_t__ arch_get_random_int (unsigned int*) ; 
 TYPE_1__* current ; 
 unsigned int* get_cpu_var (int /*<<< orphan*/ ) ; 
 scalar_t__ get_cycles () ; 
 int /*<<< orphan*/  get_random_int_hash ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  md5_transform (unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_cpu_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_int_secret ; 

unsigned int get_random_int(void)
{
	__u32 *hash;
	unsigned int ret;

	if (arch_get_random_int(&ret))
		return ret;

	hash = get_cpu_var(get_random_int_hash);

	hash[0] += current->pid + jiffies + get_cycles();
	md5_transform(hash, random_int_secret);
	ret = hash[0];
	put_cpu_var(get_random_int_hash);

	return ret;
}