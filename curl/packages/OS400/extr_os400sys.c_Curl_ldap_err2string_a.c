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
 int /*<<< orphan*/  LK_LDAP_ERROR ; 
 int /*<<< orphan*/  ldap_err2string (int) ; 
 char* set_thread_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *
Curl_ldap_err2string_a(int error)

{
  return set_thread_string(LK_LDAP_ERROR, ldap_err2string(error));
}