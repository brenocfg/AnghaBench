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

__attribute__((used)) static void
copybyte(int c, void *arg)
{
	/*
	 * arg is a pointer (outside pointer) to the pointer
	 * (inside pointer) which points to the character.
	 * We pass a double pointer, so that we can increment
	 * the inside pointer.
	 */
	char** p = arg;	/* cast outside pointer */
	**p = c;	/* store character */
	(*p)++;		/* increment inside pointer */
}