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
struct item_head {int /*<<< orphan*/  ih_key; } ;

/* Variables and functions */
 scalar_t__ KEY_FORMAT_3_6 ; 
 int ih_free_space (struct item_head*) ; 
 int ih_item_len (struct item_head*) ; 
 int ih_location (struct item_head*) ; 
 scalar_t__ ih_version (struct item_head*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  sprintf_le_key (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void sprintf_item_head(char *buf, struct item_head *ih)
{
	if (ih) {
		strcpy(buf,
		       (ih_version(ih) == KEY_FORMAT_3_6) ? "*3.6* " : "*3.5*");
		sprintf_le_key(buf + strlen(buf), &(ih->ih_key));
		sprintf(buf + strlen(buf), ", item_len %d, item_location %d, "
			"free_space(entry_count) %d",
			ih_item_len(ih), ih_location(ih), ih_free_space(ih));
	} else
		sprintf(buf, "[NULL]");
}