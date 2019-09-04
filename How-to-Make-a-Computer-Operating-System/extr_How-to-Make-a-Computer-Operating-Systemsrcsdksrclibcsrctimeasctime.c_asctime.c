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
typedef  int /*<<< orphan*/  tm_t ;

/* Variables and functions */
 int /*<<< orphan*/  asctime_buffer ; 
 char* asctime_r (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

char* asctime( const tm_t* tm ) {
    return asctime_r( tm, asctime_buffer );
}