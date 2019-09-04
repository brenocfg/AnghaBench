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
struct label {int dummy; } ;

/* Variables and functions */
 scalar_t__ bcmp (struct label*,struct label*,int) ; 

int
mac_cred_label_compare(struct label *a, struct label *b)
{
	return (bcmp(a, b, sizeof (*a)) == 0);
}