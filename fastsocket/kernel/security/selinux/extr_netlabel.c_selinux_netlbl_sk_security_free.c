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
struct sk_security_struct {int /*<<< orphan*/ * nlbl_secattr; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlbl_secattr_free (int /*<<< orphan*/ *) ; 

void selinux_netlbl_sk_security_free(struct sk_security_struct *ssec)
{
	if (ssec->nlbl_secattr != NULL)
		netlbl_secattr_free(ssec->nlbl_secattr);
}