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
struct dso {char* long_name; int /*<<< orphan*/  build_id; int /*<<< orphan*/  has_build_id; int /*<<< orphan*/  long_name_len; } ;
typedef  enum dso_binary_type { ____Placeholder_dso_binary_type } dso_binary_type ;
struct TYPE_2__ {char* symfs; } ;

/* Variables and functions */
 int BUILD_ID_SIZE ; 
#define  DSO_BINARY_TYPE__BUILDID_DEBUGINFO 141 
#define  DSO_BINARY_TYPE__BUILD_ID_CACHE 140 
#define  DSO_BINARY_TYPE__DEBUGLINK 139 
#define  DSO_BINARY_TYPE__FEDORA_DEBUGINFO 138 
#define  DSO_BINARY_TYPE__GUEST_KALLSYMS 137 
#define  DSO_BINARY_TYPE__GUEST_KMODULE 136 
#define  DSO_BINARY_TYPE__GUEST_VMLINUX 135 
#define  DSO_BINARY_TYPE__JAVA_JIT 134 
#define  DSO_BINARY_TYPE__KALLSYMS 133 
#define  DSO_BINARY_TYPE__NOT_FOUND 132 
#define  DSO_BINARY_TYPE__SYSTEM_PATH_DSO 131 
#define  DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE 130 
#define  DSO_BINARY_TYPE__UBUNTU_DEBUGINFO 129 
#define  DSO_BINARY_TYPE__VMLINUX 128 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/ * dso__build_id_filename (struct dso*,char*,size_t) ; 
 int /*<<< orphan*/  filename__read_debuglink (char*,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*,...) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 TYPE_1__ symbol_conf ; 

int dso__binary_type_file(struct dso *dso, enum dso_binary_type type,
			  char *root_dir, char *file, size_t size)
{
	char build_id_hex[BUILD_ID_SIZE * 2 + 1];
	int ret = 0;

	switch (type) {
	case DSO_BINARY_TYPE__DEBUGLINK: {
		char *debuglink;

		strncpy(file, dso->long_name, size);
		debuglink = file + dso->long_name_len;
		while (debuglink != file && *debuglink != '/')
			debuglink--;
		if (*debuglink == '/')
			debuglink++;
		filename__read_debuglink(dso->long_name, debuglink,
					 size - (debuglink - file));
		}
		break;
	case DSO_BINARY_TYPE__BUILD_ID_CACHE:
		/* skip the locally configured cache if a symfs is given */
		if (symbol_conf.symfs[0] ||
		    (dso__build_id_filename(dso, file, size) == NULL))
			ret = -1;
		break;

	case DSO_BINARY_TYPE__FEDORA_DEBUGINFO:
		snprintf(file, size, "%s/usr/lib/debug%s.debug",
			 symbol_conf.symfs, dso->long_name);
		break;

	case DSO_BINARY_TYPE__UBUNTU_DEBUGINFO:
		snprintf(file, size, "%s/usr/lib/debug%s",
			 symbol_conf.symfs, dso->long_name);
		break;

	case DSO_BINARY_TYPE__BUILDID_DEBUGINFO:
		if (!dso->has_build_id) {
			ret = -1;
			break;
		}

		build_id__sprintf(dso->build_id,
				  sizeof(dso->build_id),
				  build_id_hex);
		snprintf(file, size,
			 "%s/usr/lib/debug/.build-id/%.2s/%s.debug",
			 symbol_conf.symfs, build_id_hex, build_id_hex + 2);
		break;

	case DSO_BINARY_TYPE__SYSTEM_PATH_DSO:
		snprintf(file, size, "%s%s",
			 symbol_conf.symfs, dso->long_name);
		break;

	case DSO_BINARY_TYPE__GUEST_KMODULE:
		snprintf(file, size, "%s%s%s", symbol_conf.symfs,
			 root_dir, dso->long_name);
		break;

	case DSO_BINARY_TYPE__SYSTEM_PATH_KMODULE:
		snprintf(file, size, "%s%s", symbol_conf.symfs,
			 dso->long_name);
		break;

	default:
	case DSO_BINARY_TYPE__KALLSYMS:
	case DSO_BINARY_TYPE__VMLINUX:
	case DSO_BINARY_TYPE__GUEST_KALLSYMS:
	case DSO_BINARY_TYPE__GUEST_VMLINUX:
	case DSO_BINARY_TYPE__JAVA_JIT:
	case DSO_BINARY_TYPE__NOT_FOUND:
		ret = -1;
		break;
	}

	return ret;
}