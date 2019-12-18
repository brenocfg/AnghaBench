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
 int /*<<< orphan*/  f () ; 
 int /*<<< orphan*/  g (int**,int**) ; 
 int** x ; 
 int** y ; 

main() {
	int z[3][4];
	int i, j, *p;

	for (i = 0; i < 3; i++) {
		for (j = 0; j < 4; j++)
			x[i][j] = 1000*i + j;
		y[i] = x[i];
	}
	f();
	for (i = 0; i < 3; i++) {
		y[i] = p = &z[i][0];
		for (j = 0; j < 4; j++)
			p[j] = x[i][j];
	}
	g(z, y);
	return 0;
}