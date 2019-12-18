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
struct TYPE_2__ {scalar_t__ is_msix; } ;
struct msi_desc {TYPE_1__ msi_attrib; } ;
struct msi_attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t show_msi_mode(struct msi_desc *entry, struct msi_attribute *atr,
			     char *buf)
{
	return sprintf(buf, "%s\n", entry->msi_attrib.is_msix ? "msix" : "msi");
}