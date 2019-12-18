#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * ldap; int /*<<< orphan*/  credentials; int /*<<< orphan*/  hostent; } ;
typedef  TYPE_1__ ALD ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (TYPE_1__*) ; 
 int /*<<< orphan*/  amu_ldap_unbind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ald_free(ALD *a)
{
  he_free(a->hostent);
  cr_free(a->credentials);
  if (a->ldap != NULL)
    amu_ldap_unbind(a->ldap);
  XFREE(a);
}