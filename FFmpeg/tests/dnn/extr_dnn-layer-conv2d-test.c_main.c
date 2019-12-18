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
 scalar_t__ test_with_same_dilate () ; 
 scalar_t__ test_with_valid () ; 

int main(int argc, char **argv)
{
    if (test_with_valid())
        return 1;
    if (test_with_same_dilate())
        return 1;

    return 0;
}