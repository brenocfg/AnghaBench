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
typedef  double* vec3_t ;

/* Variables and functions */

__attribute__((used)) static void CM_Subdivide( vec3_t a, vec3_t b, vec3_t c, vec3_t out1, vec3_t out2, vec3_t out3 ) {
	int		i;

	for ( i = 0 ; i < 3 ; i++ ) {
		out1[i] = 0.5 * (a[i] + b[i]);
		out3[i] = 0.5 * (b[i] + c[i]);
		out2[i] = 0.5 * (out1[i] + out3[i]);
	}
}