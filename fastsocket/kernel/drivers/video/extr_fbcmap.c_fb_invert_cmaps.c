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
typedef  size_t u_int ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * blue16 ; 
 int /*<<< orphan*/ * blue2 ; 
 int /*<<< orphan*/ * blue4 ; 
 int /*<<< orphan*/ * blue8 ; 
 int /*<<< orphan*/ * green16 ; 
 int /*<<< orphan*/ * green2 ; 
 int /*<<< orphan*/ * green4 ; 
 int /*<<< orphan*/ * green8 ; 
 int /*<<< orphan*/ * red16 ; 
 int /*<<< orphan*/ * red2 ; 
 int /*<<< orphan*/ * red4 ; 
 int /*<<< orphan*/ * red8 ; 

void fb_invert_cmaps(void)
{
    u_int i;

    for (i = 0; i < ARRAY_SIZE(red2); i++) {
	red2[i] = ~red2[i];
	green2[i] = ~green2[i];
	blue2[i] = ~blue2[i];
    }
    for (i = 0; i < ARRAY_SIZE(red4); i++) {
	red4[i] = ~red4[i];
	green4[i] = ~green4[i];
	blue4[i] = ~blue4[i];
    }
    for (i = 0; i < ARRAY_SIZE(red8); i++) {
	red8[i] = ~red8[i];
	green8[i] = ~green8[i];
	blue8[i] = ~blue8[i];
    }
    for (i = 0; i < ARRAY_SIZE(red16); i++) {
	red16[i] = ~red16[i];
	green16[i] = ~green16[i];
	blue16[i] = ~blue16[i];
    }
}