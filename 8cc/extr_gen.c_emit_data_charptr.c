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
 int /*<<< orphan*/  emit (char*,...) ; 
 int /*<<< orphan*/  emit_label (char*) ; 
 char* make_label () ; 
 char* quote_cstring (char*) ; 

__attribute__((used)) static void emit_data_charptr(char *s, int depth) {
    char *label = make_label();
    emit(".data %d", depth + 1);
    emit_label(label);
    emit(".string \"%s\"", quote_cstring(s));
    emit(".data %d", depth);
    emit(".quad %s", label);
}