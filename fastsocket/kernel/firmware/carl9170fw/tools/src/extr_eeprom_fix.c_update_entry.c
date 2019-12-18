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
struct carl9170fw_fix_entry {int /*<<< orphan*/  value; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
update_entry(char option, struct carl9170fw_fix_entry *entry,
	     struct carl9170fw_fix_entry *fix)
{
	switch (option) {
	case '=':
		entry->mask = fix->mask;
		entry->value = fix->value;
		break;

	case 'O':
		entry->mask |= fix->mask;
		entry->value |= fix->value;
		break;

	case 'A':
		entry->mask &= fix->mask;
		entry->value &= fix->value;
		break;

	default:
		fprintf(stderr, "Unknown option: '%c'\n", option);
		return -EINVAL;
	}

	return 0;
}