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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_heads_path ; 

int valid_disk(void)
{
	int fd = open(unload_heads_path, O_RDONLY);
	if (fd < 0) {
		perror(unload_heads_path);
		return 0;
	}

	close(fd);
	return 1;
}