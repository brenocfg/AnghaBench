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
typedef  int zfs_deleg_note_t ;

/* Variables and functions */
#define  ZFS_DELEG_NOTE_GROUPQUOTA 132 
#define  ZFS_DELEG_NOTE_GROUPUSED 131 
#define  ZFS_DELEG_NOTE_USERPROP 130 
#define  ZFS_DELEG_NOTE_USERQUOTA 129 
#define  ZFS_DELEG_NOTE_USERUSED 128 
 char const* gettext (char*) ; 

__attribute__((used)) static inline const char *
deleg_perm_type(zfs_deleg_note_t note)
{
	/* subcommands */
	switch (note) {
		/* SUBCOMMANDS */
		/* OTHER */
	case ZFS_DELEG_NOTE_GROUPQUOTA:
	case ZFS_DELEG_NOTE_GROUPUSED:
	case ZFS_DELEG_NOTE_USERPROP:
	case ZFS_DELEG_NOTE_USERQUOTA:
	case ZFS_DELEG_NOTE_USERUSED:
		/* other */
		return (gettext("other"));
	default:
		return (gettext("subcommand"));
	}
}