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
typedef  int u_long ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  check (char const*) ; 
 int /*<<< orphan*/  finish ; 
 int /*<<< orphan*/  require_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static kern_return_t
extract_inner_string(const char *str, const char *prefix, const char *suffix, 
    char *buf, u_long len)
{
    kern_return_t rval = KERN_FAILURE;
    u_long prelen = 0, suflen = 0, striplen = 0;

    check(str);
    check(buf);

    prelen = (prefix) ? strlen(prefix) : 0;
    suflen = (suffix) ? strlen(suffix) : 0;
    striplen = strlen(str) - prelen - suflen;

    require_action(striplen < len, finish, rval=KERN_FAILURE);

    strncpy(buf, str + prelen, striplen);
    buf[striplen] = '\0';

    rval = KERN_SUCCESS;
finish:
    return rval;
}