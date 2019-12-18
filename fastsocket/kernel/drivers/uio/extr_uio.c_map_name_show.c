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
struct uio_mem {char* name; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ssize_t map_name_show(struct uio_mem *mem, char *buf)
{
	if (unlikely(!mem->name))
		mem->name = "";

	return sprintf(buf, "%s\n", mem->name);
}