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
typedef  int /*<<< orphan*/  sfmt_t ;

/* Variables and functions */
 scalar_t__ alloca (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int sfmt_genrand_uint32 (int /*<<< orphan*/ *) ; 

void sfmt_genrand_shuffle(sfmt_t * sfmt, void *array, int size, int rsize) {
	int i, j;
	char *t = (char *)alloca(rsize);
	char *ptr = (char *)array;
	char *ptri = ptr + (size - 1) * rsize;
	for (i = size - 1; i >= 0; i--) {
		j = sfmt_genrand_uint32(sfmt) % (i + 1);
		if (i != j)
		{
			char *ptrj = ptr + j * rsize;
			memcpy(t, ptri, rsize);
			memcpy(ptri, ptrj, rsize);
			memcpy(ptrj, t, rsize);
		}
		ptri -= rsize;
	}
}