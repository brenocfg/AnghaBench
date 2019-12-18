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
struct TYPE_2__ {scalar_t__ kptr_restrict; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* realpath (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static bool symbol__restricted_filename(const char *filename,
					const char *restricted_filename)
{
	bool restricted = false;

	if (symbol_conf.kptr_restrict) {
		char *r = realpath(filename, NULL);

		if (r != NULL) {
			restricted = strcmp(r, restricted_filename) == 0;
			free(r);
			return restricted;
		}
	}

	return restricted;
}