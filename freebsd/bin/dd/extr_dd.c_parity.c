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
typedef  int u_char ;

/* Variables and functions */

__attribute__((used)) static int
parity(u_char c)
{
	int i;

	i = c ^ (c >> 1) ^ (c >> 2) ^ (c >> 3) ^ 
	    (c >> 4) ^ (c >> 5) ^ (c >> 6) ^ (c >> 7);
	return (i & 1);
}