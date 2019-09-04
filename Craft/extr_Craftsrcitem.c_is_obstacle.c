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
 int ABS (int) ; 
#define  CLOUD 129 
#define  EMPTY 128 
 scalar_t__ is_plant (int) ; 

int is_obstacle(int w) {
    w = ABS(w);
    if (is_plant(w)) {
        return 0;
    }
    switch (w) {
        case EMPTY:
        case CLOUD:
            return 0;
        default:
            return 1;
    }
}