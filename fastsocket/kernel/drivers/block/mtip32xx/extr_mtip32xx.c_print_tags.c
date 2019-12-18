#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tagmap ;
struct driver_data {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SLOTBITS_IN_LONGS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,char*,unsigned char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int sprintf (unsigned char*,char*,unsigned long) ; 

__attribute__((used)) static void print_tags(struct driver_data *dd,
			char *msg,
			unsigned long *tagbits,
			int cnt)
{
	unsigned char tagmap[128];
	int group, tagmap_len = 0;

	memset(tagmap, 0, sizeof(tagmap));
	for (group = SLOTBITS_IN_LONGS; group > 0; group--)
		tagmap_len = sprintf(tagmap + tagmap_len, "%016lX ",
						tagbits[group-1]);
	dev_warn(&dd->pdev->dev,
			"%d command(s) %s: tagmap [%s]", cnt, msg, tagmap);
}