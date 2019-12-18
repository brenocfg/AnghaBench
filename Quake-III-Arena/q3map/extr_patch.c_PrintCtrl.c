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
typedef  int /*<<< orphan*/ * vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  _printf (char*,...) ; 

void PrintCtrl( vec3_t ctrl[9] ) {
	int		i, j;

	for ( i = 0 ; i < 3 ; i++ ) {
		for ( j = 0 ; j < 3 ; j++ ) {
			_printf("(%5.2f %5.2f %5.2f) ", ctrl[i*3+j][0], ctrl[i*3+j][1], ctrl[i*3+j][2] );
		}
		_printf("\n");
	}
}