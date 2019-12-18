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
typedef  int /*<<< orphan*/  Type ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/ * type_llong ; 
 int /*<<< orphan*/ * type_long ; 
 int /*<<< orphan*/ * type_uint ; 
 int /*<<< orphan*/ * type_ullong ; 
 int /*<<< orphan*/ * type_ulong ; 

__attribute__((used)) static Type *read_int_suffix(char *s) {
    if (!strcasecmp(s, "u"))
        return type_uint;
    if (!strcasecmp(s, "l"))
        return type_long;
    if (!strcasecmp(s, "ul") || !strcasecmp(s, "lu"))
        return type_ulong;
    if (!strcasecmp(s, "ll"))
        return type_llong;
    if (!strcasecmp(s, "ull") || !strcasecmp(s, "llu"))
        return type_ullong;
    return NULL;
}