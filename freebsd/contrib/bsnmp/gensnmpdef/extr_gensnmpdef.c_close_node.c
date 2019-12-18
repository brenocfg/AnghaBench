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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ cut ; 
 int /*<<< orphan*/  pindent (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static u_int
close_node(u_int n, u_int level)
{
	while (n--) {
		pindent(level);
		level--;
		if (level >= cut)
			printf(")\n");
	}
	return (level);
}