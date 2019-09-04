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

void Mul(int** matrixA, int** matrixB, int** matrixC)    
{    
	for(int i = 0; i < 2; ++i)     
	{    
		for(int j = 0; j < 2; ++j)     
		{    
			matrixC[i][j] = 0;    
			for(int k = 0; k < 2; ++k)     
			{    
				matrixC[i][j] += matrixA[i][k] * matrixB[k][j];    
			}    
		}    
	}    
}