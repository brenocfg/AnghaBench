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
typedef  int /*<<< orphan*/  debug_ucred ;

/* Variables and functions */
 int /*<<< orphan*/  dump_cred (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

void dump_cred_hash_table( debug_ucred * credp, size_t buf_size )
{
	int		i, my_count = (buf_size / sizeof(debug_ucred));
	
	printf("\n\t dumping credential hash table - total creds %d \n", 
			my_count);
	for (i = 0; i < my_count; i++) {
		printf("[%02d] ", i);
		dump_cred( credp );
		credp++;
	}
	return;
}