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
typedef  scalar_t__ Value_t ;

/* Variables and functions */
 unsigned int* F ; 
 scalar_t__* INDEX ; 
 scalar_t__** R ; 
 int* VERTICES ; 
 scalar_t__ infinity ; 
 int tokensetsize ; 
 size_t top ; 

__attribute__((used)) static void
traverse(int i)
{
    unsigned *fp1;
    unsigned *fp2;
    unsigned *fp3;
    int j;
    Value_t *rp;

    Value_t height;
    unsigned *base;

    VERTICES[++top] = (Value_t)i;
    INDEX[i] = height = top;

    base = F + i * tokensetsize;
    fp3 = base + tokensetsize;

    rp = R[i];
    if (rp)
    {
	while ((j = *rp++) >= 0)
	{
	    if (INDEX[j] == 0)
		traverse(j);

	    if (INDEX[i] > INDEX[j])
		INDEX[i] = INDEX[j];

	    fp1 = base;
	    fp2 = F + j * tokensetsize;

	    while (fp1 < fp3)
		*fp1++ |= *fp2++;
	}
    }

    if (INDEX[i] == height)
    {
	for (;;)
	{
	    j = VERTICES[top--];
	    INDEX[j] = infinity;

	    if (i == j)
		break;

	    fp1 = base;
	    fp2 = F + j * tokensetsize;

	    while (fp1 < fp3)
		*fp2++ = *fp1++;
	}
    }
}