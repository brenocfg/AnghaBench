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
 int clock () ; 
 int getpid () ; 
 int getppid () ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int w ; 
 int /*<<< orphan*/  x ; 
 int y ; 
 int z ; 

void rand_init(void)
{
    x = time(NULL);
    y = getpid() ^ getppid();
    z = clock();
    w = z ^ y;
}