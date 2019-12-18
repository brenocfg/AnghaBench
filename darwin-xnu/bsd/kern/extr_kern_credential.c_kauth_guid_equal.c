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
typedef  int /*<<< orphan*/  guid_t ;

/* Variables and functions */
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
kauth_guid_equal(guid_t *guid1, guid_t *guid2)
{
	return(bcmp(guid1, guid2, sizeof(*guid1)) == 0);
}