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
 int /*<<< orphan*/  AutoReboot () ; 
 int CARTRIDGE_Insert (char const*) ; 

int CARTRIDGE_InsertAutoReboot(const char *filename)
{
	int result = CARTRIDGE_Insert(filename);
	AutoReboot();
	return result;
}