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
struct carlfw_list_entry {int dummy; } ;
struct carlfw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  carlfw_entry_unlink (struct carlfw*,struct carlfw_list_entry*) ; 
 int /*<<< orphan*/  free (struct carlfw_list_entry*) ; 

__attribute__((used)) static void carlfw_entry_del(struct carlfw *fw,
	struct carlfw_list_entry *entry)
{
	carlfw_entry_unlink(fw, entry);
	free(entry);
}