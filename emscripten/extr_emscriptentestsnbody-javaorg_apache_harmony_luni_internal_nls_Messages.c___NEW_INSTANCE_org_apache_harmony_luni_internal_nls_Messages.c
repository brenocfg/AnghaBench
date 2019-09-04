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
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  JAVA_NULL ; 
 int /*<<< orphan*/  __NEW_org_apache_harmony_luni_internal_nls_Messages () ; 
 int /*<<< orphan*/  org_apache_harmony_luni_internal_nls_Messages___INIT___ (int /*<<< orphan*/ ) ; 

JAVA_OBJECT __NEW_INSTANCE_org_apache_harmony_luni_internal_nls_Messages()
{
    JAVA_OBJECT me = JAVA_NULL;
    me = __NEW_org_apache_harmony_luni_internal_nls_Messages();
    org_apache_harmony_luni_internal_nls_Messages___INIT___(me);
    return me;
}