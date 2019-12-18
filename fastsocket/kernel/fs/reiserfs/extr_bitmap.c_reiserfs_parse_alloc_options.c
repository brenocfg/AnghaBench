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
struct super_block {int dummy; } ;
struct TYPE_3__ {int border; int large_file_size; int preallocmin; int preallocsize; scalar_t__ bits; } ;
struct TYPE_4__ {TYPE_1__ s_alloc_options; } ;

/* Variables and functions */
 int PREALLOCATION_SIZE ; 
 TYPE_2__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  SB_ALLOC_OPTS (struct super_block*) ; 
 int /*<<< orphan*/  SET_OPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  concentrating_formatted_nodes ; 
 int /*<<< orphan*/  dirid_groups ; 
 int /*<<< orphan*/  displace_based_on_dirid ; 
 int /*<<< orphan*/  displacing_large_files ; 
 int /*<<< orphan*/  displacing_new_packing_localities ; 
 int /*<<< orphan*/  hashed_formatted_nodes ; 
 int /*<<< orphan*/  hundredth_slices ; 
 int /*<<< orphan*/  new_hashed_relocation ; 
 int /*<<< orphan*/  oid_groups ; 
 int /*<<< orphan*/  old_hashed_relocation ; 
 int /*<<< orphan*/  old_way ; 
 int /*<<< orphan*/  packing_groups ; 
 int /*<<< orphan*/  reiserfs_info (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,char*) ; 
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_busy ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strsep (char**,char*) ; 

int reiserfs_parse_alloc_options(struct super_block *s, char *options)
{
	char *this_char, *value;

	REISERFS_SB(s)->s_alloc_options.bits = 0;	/* clear default settings */

	while ((this_char = strsep(&options, ":")) != NULL) {
		if ((value = strchr(this_char, '=')) != NULL)
			*value++ = 0;

		if (!strcmp(this_char, "concentrating_formatted_nodes")) {
			int temp;
			SET_OPTION(concentrating_formatted_nodes);
			temp = (value
				&& *value) ? simple_strtoul(value, &value,
							    0) : 10;
			if (temp <= 0 || temp > 100) {
				REISERFS_SB(s)->s_alloc_options.border = 10;
			} else {
				REISERFS_SB(s)->s_alloc_options.border =
				    100 / temp;
			}
			continue;
		}
		if (!strcmp(this_char, "displacing_large_files")) {
			SET_OPTION(displacing_large_files);
			REISERFS_SB(s)->s_alloc_options.large_file_size =
			    (value
			     && *value) ? simple_strtoul(value, &value, 0) : 16;
			continue;
		}
		if (!strcmp(this_char, "displacing_new_packing_localities")) {
			SET_OPTION(displacing_new_packing_localities);
			continue;
		};

		if (!strcmp(this_char, "old_hashed_relocation")) {
			SET_OPTION(old_hashed_relocation);
			continue;
		}

		if (!strcmp(this_char, "new_hashed_relocation")) {
			SET_OPTION(new_hashed_relocation);
			continue;
		}

		if (!strcmp(this_char, "dirid_groups")) {
			SET_OPTION(dirid_groups);
			continue;
		}
		if (!strcmp(this_char, "oid_groups")) {
			SET_OPTION(oid_groups);
			continue;
		}
		if (!strcmp(this_char, "packing_groups")) {
			SET_OPTION(packing_groups);
			continue;
		}
		if (!strcmp(this_char, "hashed_formatted_nodes")) {
			SET_OPTION(hashed_formatted_nodes);
			continue;
		}

		if (!strcmp(this_char, "skip_busy")) {
			SET_OPTION(skip_busy);
			continue;
		}

		if (!strcmp(this_char, "hundredth_slices")) {
			SET_OPTION(hundredth_slices);
			continue;
		}

		if (!strcmp(this_char, "old_way")) {
			SET_OPTION(old_way);
			continue;
		}

		if (!strcmp(this_char, "displace_based_on_dirid")) {
			SET_OPTION(displace_based_on_dirid);
			continue;
		}

		if (!strcmp(this_char, "preallocmin")) {
			REISERFS_SB(s)->s_alloc_options.preallocmin =
			    (value
			     && *value) ? simple_strtoul(value, &value, 0) : 4;
			continue;
		}

		if (!strcmp(this_char, "preallocsize")) {
			REISERFS_SB(s)->s_alloc_options.preallocsize =
			    (value
			     && *value) ? simple_strtoul(value, &value,
							 0) :
			    PREALLOCATION_SIZE;
			continue;
		}

		reiserfs_warning(s, "zam-4001", "unknown option - %s",
				 this_char);
		return 1;
	}

	reiserfs_info(s, "allocator options = [%08x]\n", SB_ALLOC_OPTS(s));
	return 0;
}