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
 char* vfd ; 
 int vfd_cursor ; 

__attribute__((used)) static void scroll_vfd( void )
{
	int	i;

	for (i=0; i<20; i++) {
		vfd[i] = vfd[i+20];
		vfd[i+20] = ' ';
	}
	vfd_cursor = 20;
}