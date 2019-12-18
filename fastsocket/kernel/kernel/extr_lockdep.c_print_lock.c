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
struct held_lock {int /*<<< orphan*/  acquire_ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlock_class (struct held_lock*) ; 
 int /*<<< orphan*/  print_ip_sym (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_lock_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static void print_lock(struct held_lock *hlock)
{
	print_lock_name(hlock_class(hlock));
	printk(", at: ");
	print_ip_sym(hlock->acquire_ip);
}