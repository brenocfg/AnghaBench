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
 int /*<<< orphan*/  exit (int) ; 
 int len_config ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/ * realloc (int /*<<< orphan*/ *,int) ; 
 int size_config ; 
 int /*<<< orphan*/ * str_config ; 

__attribute__((used)) static void grow_config(int len)
{
	while (len_config + len > size_config) {
		if (size_config == 0)
			size_config = 2048;
		str_config = realloc(str_config, size_config *= 2);
		if (str_config == NULL)
			{ perror("fixdep:malloc"); exit(1); }
	}
}