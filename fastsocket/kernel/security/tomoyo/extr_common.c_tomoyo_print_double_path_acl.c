#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct tomoyo_io_buffer {int read_bit; int read_avail; } ;
struct tomoyo_double_path_acl_record {int perm; TYPE_2__* filename2; TYPE_1__* filename1; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int TOMOYO_MAX_DOUBLE_PATH_OPERATION ; 
 char* tomoyo_dp2keyword (int) ; 
 int /*<<< orphan*/  tomoyo_io_printf (struct tomoyo_io_buffer*,char*,char const*,char const*,char const*,char const*,char const*) ; 

__attribute__((used)) static bool tomoyo_print_double_path_acl(struct tomoyo_io_buffer *head,
					 struct tomoyo_double_path_acl_record *
					 ptr)
{
	int pos;
	const char *atmark1 = "";
	const char *atmark2 = "";
	const char *filename1;
	const char *filename2;
	const u8 perm = ptr->perm;
	u8 bit;

	filename1 = ptr->filename1->name;
	filename2 = ptr->filename2->name;
	for (bit = head->read_bit; bit < TOMOYO_MAX_DOUBLE_PATH_OPERATION;
	     bit++) {
		const char *msg;
		if (!(perm & (1 << bit)))
			continue;
		msg = tomoyo_dp2keyword(bit);
		pos = head->read_avail;
		if (!tomoyo_io_printf(head, "allow_%s %s%s %s%s\n", msg,
				      atmark1, filename1, atmark2, filename2))
			goto out;
	}
	head->read_bit = 0;
	return true;
 out:
	head->read_bit = bit;
	head->read_avail = pos;
	return false;
}