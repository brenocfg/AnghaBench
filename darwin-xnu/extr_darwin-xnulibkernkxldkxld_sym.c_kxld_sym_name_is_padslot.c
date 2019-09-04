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
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESERVED_TOKEN ; 
 int /*<<< orphan*/  check (char const*) ; 
 scalar_t__ kxld_strstr (char const*,int /*<<< orphan*/ ) ; 

boolean_t
kxld_sym_name_is_padslot(const char *name)
{
    check(name);

    return (kxld_strstr(name, RESERVED_TOKEN) != 0);
}