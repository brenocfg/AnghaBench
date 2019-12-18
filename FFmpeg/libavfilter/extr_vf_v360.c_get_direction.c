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
 int BACK ; 
 int DOWN ; 
 int FRONT ; 
 int LEFT ; 
 int RIGHT ; 
 int UP ; 

__attribute__((used)) static int get_direction(char c)
{
    switch (c) {
    case 'r':
        return RIGHT;
    case 'l':
        return LEFT;
    case 'u':
        return UP;
    case 'd':
        return DOWN;
    case 'f':
        return FRONT;
    case 'b':
        return BACK;
    default:
        return -1;
    }
}