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
struct netlbl_audit {int /*<<< orphan*/  secid; int /*<<< orphan*/  sessionid; int /*<<< orphan*/  loginuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  audit_get_loginuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audit_get_sessionid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_security () ; 
 int /*<<< orphan*/  smack_to_secid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smk_netlabel_audit_set(struct netlbl_audit *nap)
{
	nap->loginuid = audit_get_loginuid(current);
	nap->sessionid = audit_get_sessionid(current);
	nap->secid = smack_to_secid(current_security());
}