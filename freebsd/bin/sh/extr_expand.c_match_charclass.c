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
typedef  scalar_t__ wctype_t ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int iswctype (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 char* strstr (char const*,char*) ; 
 scalar_t__ wctype (char*) ; 

__attribute__((used)) static int
match_charclass(const char *p, wchar_t chr, const char **end)
{
	char name[20];
	const char *nameend;
	wctype_t cclass;

	*end = NULL;
	p++;
	nameend = strstr(p, ":]");
	if (nameend == NULL || (size_t)(nameend - p) >= sizeof(name) ||
	    nameend == p)
		return 0;
	memcpy(name, p, nameend - p);
	name[nameend - p] = '\0';
	*end = nameend + 2;
	cclass = wctype(name);
	/* An unknown class matches nothing but is valid nevertheless. */
	if (cclass == 0)
		return 0;
	return iswctype(chr, cclass);
}