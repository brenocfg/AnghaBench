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
 char* gen_buf ; 
 int /*<<< orphan*/  gen_defs () ; 
 int /*<<< orphan*/  gen_foreign_headers () ; 
 int /*<<< orphan*/  gen_foreign_sources () ; 
 int /*<<< orphan*/  gen_forward_decls () ; 
 int /*<<< orphan*/  gen_postamble () ; 
 int /*<<< orphan*/  gen_preamble () ; 
 int /*<<< orphan*/  gen_sorted_decls () ; 
 int /*<<< orphan*/  gen_typeinfos () ; 
 int /*<<< orphan*/  genf (char*,char*) ; 
 int /*<<< orphan*/  genln () ; 
 int /*<<< orphan*/  preprocess_packages () ; 

void gen_all(void) {
    preprocess_packages();
    gen_buf = NULL;
    gen_foreign_headers();
    genln();
    gen_forward_decls();
    genln();
    gen_sorted_decls();
    gen_typeinfos();
    gen_defs();
    gen_foreign_sources();
    genln();
    gen_postamble();
    char *buf = gen_buf;
    gen_buf = NULL;
    gen_preamble();
    genf("%s", buf);
}