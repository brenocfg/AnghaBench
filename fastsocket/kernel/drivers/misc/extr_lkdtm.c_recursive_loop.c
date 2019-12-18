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
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  recur_count ; 

__attribute__((used)) static int recursive_loop(int a)
{
	char buf[1024];

	memset(buf,0xFF,1024);
	recur_count--;
	if (!recur_count)
		return 0;
	else
        	return recursive_loop(a);
}