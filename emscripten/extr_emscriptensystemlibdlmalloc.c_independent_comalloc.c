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
 int /*<<< orphan*/  gm ; 
 void** ialloc (int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ ,void**) ; 

void** dlindependent_comalloc(size_t n_elements, size_t sizes[],
                              void* chunks[]) {
    return ialloc(gm, n_elements, sizes, 0, chunks);
}