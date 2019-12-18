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
 int /*<<< orphan*/  fatal () ; 
 size_t mode ; 

__attribute__((used)) static void set_mode (char *buffer)
{
  	for (mode = 0;; mode++)
		if (buffer[mode] < '0' || buffer[mode] > '9')
			break;
	if (mode != 8 && mode != 16)
		fatal();
}