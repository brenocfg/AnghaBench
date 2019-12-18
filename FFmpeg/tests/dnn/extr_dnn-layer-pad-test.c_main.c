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
 scalar_t__ test_with_mode_constant () ; 
 scalar_t__ test_with_mode_reflect () ; 
 scalar_t__ test_with_mode_symmetric () ; 

int main(int argc, char **argv)
{
    if (test_with_mode_symmetric())
        return 1;

    if (test_with_mode_reflect())
        return 1;

    if (test_with_mode_constant())
        return 1;
}