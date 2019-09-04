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
typedef  scalar_t__ u_int8_t ;
struct substring {char* string; scalar_t__ length; } ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 scalar_t__ necp_check_suffix (struct substring,struct substring,int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,scalar_t__) ; 

__attribute__((used)) static bool
necp_hostname_matches_domain(struct substring hostname_substring, u_int8_t hostname_dot_count, char *domain, u_int8_t domain_dot_count)
{
	if (hostname_substring.string == NULL || domain == NULL) {
		return (hostname_substring.string == domain);
	}

	struct substring domain_substring;
	domain_substring.string = domain;
	domain_substring.length = strlen(domain);

	if (hostname_dot_count == domain_dot_count) {
		// strncasecmp does case-insensitive check for all UTF-8 strings (ignores non-ASCII characters)
		if (hostname_substring.length == domain_substring.length &&
			strncasecmp(hostname_substring.string, domain_substring.string, hostname_substring.length) == 0) {
			return (TRUE);
		}
	} else if (domain_dot_count < hostname_dot_count) {
		if (necp_check_suffix(hostname_substring, domain_substring, TRUE)) {
			return (TRUE);
		}
	}

	return (FALSE);
}