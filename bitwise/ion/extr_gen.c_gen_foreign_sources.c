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
 size_t buf_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_foreign_sources_buf ; 
 int /*<<< orphan*/  gen_include (int /*<<< orphan*/ ) ; 

void gen_foreign_sources(void) {
    for (size_t i = 0; i < buf_len(gen_foreign_sources_buf); i++) {
        gen_include(gen_foreign_sources_buf[i]);
    }
}