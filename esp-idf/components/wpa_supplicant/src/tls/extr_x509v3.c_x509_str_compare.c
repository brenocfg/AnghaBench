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

/* Variables and functions */
 int /*<<< orphan*/  os_free (char*) ; 
 char* os_strdup (char const*) ; 
 int strcasecmp (char const*,char const*) ; 
 int /*<<< orphan*/  x509_str_strip_whitespace (char*) ; 

__attribute__((used)) static int x509_str_compare(const char *a, const char *b)
{
	char *aa, *bb;
	int ret;

	if (!a && b)
		return -1;
	if (a && !b)
		return 1;
	if (!a && !b)
		return 0;

	aa = os_strdup(a);
	bb = os_strdup(b);

	if (aa == NULL || bb == NULL) {
		os_free(aa);
		os_free(bb);
		return strcasecmp(a, b);
	}

	x509_str_strip_whitespace(aa);
	x509_str_strip_whitespace(bb);

	ret = strcasecmp(aa, bb);

	os_free(aa);
	os_free(bb);

	return ret;
}