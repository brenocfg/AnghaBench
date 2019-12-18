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
struct dirent {int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int atoi (int /*<<< orphan*/ ) ; 

int seq_compare(const struct dirent **de1, const struct dirent **de2)
{
    int num1 = atoi((*de1)->d_name);
    int num2 = atoi((*de2)->d_name);
    if (num1 < num2)
    	return -1;
    else if (num1 == num2)
    	return 0;
    else
    	return 1;
}