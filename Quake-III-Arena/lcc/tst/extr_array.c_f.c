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
 int /*<<< orphan*/  printf (char*,...) ; 
 int** x ; 
 int** y ; 

f() {
	int i, j;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 4; j++)
			printf(" %d", x[i][j]);
	printf("\n");
	for (i = 0; i < 3; i++)
		for (j = 0; j < 4; j++)
			printf(" %d", y[i][j]);
	printf("\n");
}