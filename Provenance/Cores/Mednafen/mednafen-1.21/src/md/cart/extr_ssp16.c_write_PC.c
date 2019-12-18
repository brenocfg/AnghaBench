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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  SET_PC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_cycles ; 

__attribute__((used)) static void write_PC(u32 d)
{
	SET_PC(d);
	g_cycles--;
}