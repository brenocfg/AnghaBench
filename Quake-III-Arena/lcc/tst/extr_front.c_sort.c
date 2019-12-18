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
 int cmp (void const*,void const*) ; 
 int /*<<< orphan*/  qsort (char**,int,int,int (*) (void const*,void const*)) ; 

sort() {
	int n; char *a[100];
	qsort(a, n, sizeof(char*), (int (*)(const void*, const void*))cmp);
	qsort(a, n, sizeof(char*), cmp);	/* error */
}