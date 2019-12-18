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
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  gen_foreign_headers_buf ; 
 int /*<<< orphan*/  gen_foreign_headers_map ; 
 int /*<<< orphan*/  map_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,char const*,void*) ; 
 char* str_intern (char const*) ; 

__attribute__((used)) static void add_foreign_header(const char *name) {
    name = str_intern(name);
    if (!map_get(&gen_foreign_headers_map, name)) {
        map_put(&gen_foreign_headers_map, name, (void *)1);
        buf_push(gen_foreign_headers_buf, name);
    }
}