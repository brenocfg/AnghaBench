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
 int MAX_OPEN_FILES ; 
 int /*<<< orphan*/ ** __ps2_fdmap ; 

int is_fd_valid(int fd)
{
   /* Correct fd value */
   fd = MAX_OPEN_FILES - fd;

   return (fd >= 0) && (fd < MAX_OPEN_FILES) && (__ps2_fdmap[fd] != NULL);
}