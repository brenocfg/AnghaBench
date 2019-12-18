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
typedef  char* ulong_t ;

/* Variables and functions */
 int alist_def_print_cb_key_int ; 
 int alist_def_print_cb_value_int ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
alist_def_print_cb(void *key, void *value)
{
	printf("Key: ");
	if (alist_def_print_cb_key_int == 1)
		printf("%5lu ", (ulong_t)key);
	else
		printf("%s\n", (char *)key);

	printf("Value: ");
	if (alist_def_print_cb_value_int == 1)
		printf("%5lu\n", (ulong_t)value);
	else
		printf("%s\n", (char *)key);

	return (1);
}