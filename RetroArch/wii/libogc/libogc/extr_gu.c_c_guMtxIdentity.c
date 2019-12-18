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
typedef  int s32 ;
typedef  double** Mtx ;

/* Variables and functions */

void c_guMtxIdentity(Mtx mt)
{
	s32 i,j;

	for(i=0;i<3;i++) {
		for(j=0;j<4;j++) {
			if(i==j) mt[i][j] = 1.0;
			else mt[i][j] = 0.0;
		}
	}
}