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
 int /*<<< orphan*/  esp_fill_random (unsigned char*,size_t) ; 

__attribute__((used)) static int myrand( void *rng_state, unsigned char *output, size_t len )
{
    esp_fill_random(output, len);
    return( 0 );
}