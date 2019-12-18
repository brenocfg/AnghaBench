#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct Block_layout {TYPE_1__* descriptor; } ;
struct TYPE_2__ {unsigned long size; } ;

/* Variables and functions */

unsigned long int Block_size(void *arg) {
    return ((struct Block_layout *)arg)->descriptor->size;
}