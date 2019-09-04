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
 int /*<<< orphan*/  strftime (char*,int,char*,int /*<<< orphan*/  const*) ; 

char* asctime_r( const tm_t* tm, char* buf ) {
    strftime( buf, 26, "%a %b %d %H:%M:%S %Y\n", tm );

    return buf;
}