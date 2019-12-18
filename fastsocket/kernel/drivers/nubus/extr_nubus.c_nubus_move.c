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
 int /*<<< orphan*/  nubus_advance (unsigned char**,int,int) ; 
 int /*<<< orphan*/  nubus_rewind (unsigned char**,int,int) ; 

__attribute__((used)) static void nubus_move(unsigned char **ptr, int len, int map)
{
	if(len > 0)
		nubus_advance(ptr, len, map);
	else if(len < 0)
		nubus_rewind(ptr, -len, map);
}