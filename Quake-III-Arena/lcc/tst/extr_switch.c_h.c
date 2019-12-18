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

h()
{
	int i, n=0;

	printf("h:\n");
	for (i = 1; i <= 500; i++)
		switch (i) {
		default: n++; continue;
		case 128: printf("i = %d\n", i); break;
		case 16: printf("i = %d\n", i); break;
		case 8: printf("i = %d\n", i); break;
		case 120: printf("i = %d\n", i); break;
		case 280: printf("i = %d\n", i); break;
		case 264: printf("i = %d\n", i); break;
		case 248: printf("i = %d\n", i); break;
		case 272: printf("i = %d\n", i); break;
		case 304: printf("i = %d\n", i); break;
		case 296: printf("i = %d\n", i); break;
		case 288: printf("i = %d\n", i); break;
		case 312: printf("i = %d\n", i); break;
		}
	printf("%d defaults\n", n);
}