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
typedef  int /*<<< orphan*/  GucSource ;

/* Variables and functions */
 int CheckConninfo (char*,char const**,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  GUC_check_errdetail (char*,char*) ; 
 int /*<<< orphan*/  lengthof (char const**) ; 

__attribute__((used)) static bool
NodeConninfoGucCheckHook(char **newval, void **extra, GucSource source)
{
	/* this array _must_ be kept in an order usable by bsearch */
	const char *whitelist[] = {
		"application_name",
		"connect_timeout",
			#if defined(ENABLE_GSS) && defined(ENABLE_SSPI)
		"gsslib",
			#endif
		"keepalives",
		"keepalives_count",
		"keepalives_idle",
		"keepalives_interval",
			#if defined(ENABLE_GSS) || defined(ENABLE_SSPI)
		"krbsrvname",
			#endif
		"sslcompression",
		"sslcrl",
		"sslmode",
		"sslrootcert"
	};
	char *errorMsg = NULL;
	bool conninfoValid = CheckConninfo(*newval, whitelist, lengthof(whitelist),
									   &errorMsg);

	if (!conninfoValid)
	{
		GUC_check_errdetail("%s", errorMsg);
	}

	return conninfoValid;
}