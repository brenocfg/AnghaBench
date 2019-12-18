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
typedef  int /*<<< orphan*/  u64 ;
struct hists {int dummy; } ;
struct addr_location {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * __hists__add_entry (struct hists*,struct addr_location*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hists__add_entry(struct hists *self,
			    struct addr_location *al, u64 period)
{
	if (__hists__add_entry(self, al, NULL, period) != NULL)
		return 0;
	return -ENOMEM;
}