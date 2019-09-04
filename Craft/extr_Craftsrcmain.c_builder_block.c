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
 int /*<<< orphan*/  get_block (int,int,int) ; 
 scalar_t__ is_destructable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_block (int,int,int,int) ; 

void builder_block(int x, int y, int z, int w) {
    if (y <= 0 || y >= 256) {
        return;
    }
    if (is_destructable(get_block(x, y, z))) {
        set_block(x, y, z, 0);
    }
    if (w) {
        set_block(x, y, z, w);
    }
}