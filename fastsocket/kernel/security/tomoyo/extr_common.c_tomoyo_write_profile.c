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
struct tomoyo_profile {unsigned int* value; struct tomoyo_path_info const* comment; } ;
struct tomoyo_path_info {int dummy; } ;
struct tomoyo_io_buffer {char* write_buf; } ;
struct TYPE_2__ {char const* keyword; unsigned int max_value; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int TOMOYO_MAX_CONTROL_INDEX ; 
#define  TOMOYO_VERBOSE 128 
 int sscanf (char*,char*,unsigned int*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strict_strtoul (char*,int,unsigned long*) ; 
 TYPE_1__* tomoyo_control_array ; 
 struct tomoyo_profile* tomoyo_find_or_assign_new_profile (unsigned long) ; 
 char** tomoyo_mode_2 ; 
 char** tomoyo_mode_4 ; 
 struct tomoyo_path_info* tomoyo_save_name (char*) ; 

__attribute__((used)) static int tomoyo_write_profile(struct tomoyo_io_buffer *head)
{
	char *data = head->write_buf;
	unsigned int i;
	unsigned int value;
	char *cp;
	struct tomoyo_profile *profile;
	unsigned long num;

	cp = strchr(data, '-');
	if (cp)
		*cp = '\0';
	if (strict_strtoul(data, 10, &num))
		return -EINVAL;
	if (cp)
		data = cp + 1;
	profile = tomoyo_find_or_assign_new_profile(num);
	if (!profile)
		return -EINVAL;
	cp = strchr(data, '=');
	if (!cp)
		return -EINVAL;
	*cp = '\0';
	if (!strcmp(data, "COMMENT")) {
		const struct tomoyo_path_info *new_comment
			= tomoyo_save_name(cp + 1);
		if (!new_comment)
			return -ENOMEM;
		profile->comment = new_comment;
		return 0;
	}
	for (i = 0; i < TOMOYO_MAX_CONTROL_INDEX; i++) {
		if (strcmp(data, tomoyo_control_array[i].keyword))
			continue;
		if (sscanf(cp + 1, "%u", &value) != 1) {
			int j;
			const char **modes;
			switch (i) {
			case TOMOYO_VERBOSE:
				modes = tomoyo_mode_2;
				break;
			default:
				modes = tomoyo_mode_4;
				break;
			}
			for (j = 0; j < 4; j++) {
				if (strcmp(cp + 1, modes[j]))
					continue;
				value = j;
				break;
			}
			if (j == 4)
				return -EINVAL;
		} else if (value > tomoyo_control_array[i].max_value) {
			value = tomoyo_control_array[i].max_value;
		}
		profile->value[i] = value;
		return 0;
	}
	return -EINVAL;
}