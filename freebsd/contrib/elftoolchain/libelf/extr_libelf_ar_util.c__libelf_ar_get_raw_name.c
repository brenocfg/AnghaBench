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
struct ar_hdr {int /*<<< orphan*/  ar_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIBELF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RESOURCE ; 
 char* malloc (size_t const) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,size_t const) ; 

char *
_libelf_ar_get_raw_name(const struct ar_hdr *arh)
{
	char *rawname;
	const size_t namesz = sizeof(arh->ar_name);

	if ((rawname = malloc(namesz + 1)) == NULL) {
		LIBELF_SET_ERROR(RESOURCE, 0);
		return (NULL);
	}

	(void) strncpy(rawname, arh->ar_name, namesz);
	rawname[namesz] = '\0';
	return (rawname);
}