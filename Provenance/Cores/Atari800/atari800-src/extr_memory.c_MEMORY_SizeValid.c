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
 int MEMORY_RAM_320_COMPY_SHOP ; 
 int MEMORY_RAM_320_RAMBO ; 

int MEMORY_SizeValid(int size)
{
	return size == 8 || size == 16 || size == 24 || size == 32
	       || size == 40 || size == 48 || size == 52 || size == 64
	       || size == 128 || size == 192 || size == MEMORY_RAM_320_RAMBO
	       || size == MEMORY_RAM_320_COMPY_SHOP || size == 576 || size == 1088;
}