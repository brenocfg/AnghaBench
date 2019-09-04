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
struct TYPE_2__ {size_t page_size; } ;

/* Variables and functions */
 void* dlmemalign (size_t,size_t) ; 
 int /*<<< orphan*/  ensure_initialization () ; 
 TYPE_1__ mparams ; 

void* dlvalloc(size_t bytes) {
    size_t pagesz;
    ensure_initialization();
    pagesz = mparams.page_size;
    return dlmemalign(pagesz, bytes);
}