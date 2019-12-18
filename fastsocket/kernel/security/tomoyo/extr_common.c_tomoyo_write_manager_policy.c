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
struct tomoyo_io_buffer {char* write_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TOMOYO_KEYWORD_DELETE ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int tomoyo_manage_by_non_root ; 
 int tomoyo_str_starts (char**,int /*<<< orphan*/ ) ; 
 int tomoyo_update_manager_entry (char*,int) ; 

__attribute__((used)) static int tomoyo_write_manager_policy(struct tomoyo_io_buffer *head)
{
	char *data = head->write_buf;
	bool is_delete = tomoyo_str_starts(&data, TOMOYO_KEYWORD_DELETE);

	if (!strcmp(data, "manage_by_non_root")) {
		tomoyo_manage_by_non_root = !is_delete;
		return 0;
	}
	return tomoyo_update_manager_entry(data, is_delete);
}