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
 int /*<<< orphan*/  genf (char*,char const*,...) ; 
 scalar_t__ type_sizeof (int /*<<< orphan*/ *) ; 
 char* type_to_cdecl (int /*<<< orphan*/ *,char*) ; 

void gen_typeinfo_header(const char *kind, Type *type) { 
    if (type_sizeof(type) == 0) {
        genf("&(TypeInfo){%s, .size = 0, .align = 0", kind);
    } else {
        const char *ctype = type_to_cdecl(type, "");
        genf("&(TypeInfo){%s, .size = sizeof(%s), .align = alignof(%s)", kind, ctype, ctype);
    }
}