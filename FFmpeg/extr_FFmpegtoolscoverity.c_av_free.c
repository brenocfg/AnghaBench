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
 int /*<<< orphan*/  __coverity_free__ (void*) ; 
 int /*<<< orphan*/  __coverity_mark_as_afm_freed__ (void*,char*) ; 

void *av_free(void *ptr) {
    __coverity_free__(ptr);
    __coverity_mark_as_afm_freed__(ptr, "av_free");
}