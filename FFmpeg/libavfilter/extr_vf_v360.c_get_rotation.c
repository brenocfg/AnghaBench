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
 int ROT_0 ; 
 int ROT_180 ; 
 int ROT_270 ; 
 int ROT_90 ; 

__attribute__((used)) static int get_rotation(char c)
{
    switch (c) {
    case '0':
        return ROT_0;
    case '1':
        return ROT_90;
    case '2':
        return ROT_180;
    case '3':
        return ROT_270;
    default:
        return -1;
    }
}