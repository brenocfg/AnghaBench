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
struct bsd_acct_struct {int needcheck; } ;

/* Variables and functions */

__attribute__((used)) static void acct_timeout(unsigned long x)
{
	struct bsd_acct_struct *acct = (struct bsd_acct_struct *)x;
	acct->needcheck = 1;
}