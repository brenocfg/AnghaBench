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
typedef  size_t u32 ;

/* Variables and functions */
 size_t M8XX_SIZES_NO ; 
 size_t* m8xx_size_to_gray ; 

__attribute__((used)) static u32 m8xx_get_graycode(u32 size)
{
	u32 k;

	for (k = 0; k < M8XX_SIZES_NO; k++)
		if (m8xx_size_to_gray[k] == size)
			break;

	if ((k == M8XX_SIZES_NO) || (m8xx_size_to_gray[k] == -1))
		k = -1;

	return k;
}