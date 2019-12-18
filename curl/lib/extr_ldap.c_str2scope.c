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
 int LDAP_SCOPE_BASE ; 
 int LDAP_SCOPE_ONELEVEL ; 
 int LDAP_SCOPE_SUBTREE ; 
 scalar_t__ strcasecompare (char const*,char*) ; 

__attribute__((used)) static int str2scope(const char *p)
{
  if(strcasecompare(p, "one"))
    return LDAP_SCOPE_ONELEVEL;
  if(strcasecompare(p, "onetree"))
    return LDAP_SCOPE_ONELEVEL;
  if(strcasecompare(p, "base"))
    return LDAP_SCOPE_BASE;
  if(strcasecompare(p, "sub"))
    return LDAP_SCOPE_SUBTREE;
  if(strcasecompare(p, "subtree"))
    return LDAP_SCOPE_SUBTREE;
  return (-1);
}