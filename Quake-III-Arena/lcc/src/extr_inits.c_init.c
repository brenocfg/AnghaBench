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

void init(int argc, char *argv[]) {
	{extern void input_init(int, char *[]); input_init(argc, argv);}
	{extern void main_init(int, char *[]); main_init(argc, argv);}
	{extern void prof_init(int, char *[]); prof_init(argc, argv);}
	{extern void trace_init(int, char *[]); trace_init(argc, argv);}
	{extern void type_init(int, char *[]); type_init(argc, argv);}
	{extern void x86linux_init(int, char *[]); x86linux_init(argc, argv);}
}