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
struct TYPE_2__ {char* name; int version; } ;

/* Variables and functions */
 scalar_t__ eqstr_chunk (char const*,int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_1__* protocol_versions ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (char const*) ; 

unsigned
parse_version(const char *name, size_t len)
{
	size_t u;

	for (u = 0;; u ++) {
		const char *ref;

		ref = protocol_versions[u].name;
		if (ref == NULL) {
			fprintf(stderr, "ERROR: unrecognised protocol"
				" version name: '%s'\n", name);
			return 0;
		}
		if (eqstr_chunk(ref, strlen(ref), name, len)) {
			return protocol_versions[u].version;
		}
	}
}