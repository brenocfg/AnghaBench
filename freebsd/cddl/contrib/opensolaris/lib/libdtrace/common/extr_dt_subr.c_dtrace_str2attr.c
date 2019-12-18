#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ dtrace_stability_t ;
typedef  scalar_t__ dtrace_class_t ;
struct TYPE_4__ {scalar_t__ dtat_class; scalar_t__ dtat_data; scalar_t__ dtat_name; } ;
typedef  TYPE_1__ dtrace_attribute_t ;

/* Variables and functions */
 scalar_t__ DTRACE_CLASS_MAX ; 
 scalar_t__ DTRACE_STABILITY_MAX ; 
 TYPE_1__ _dtrace_maxattr ; 
 char* alloca (scalar_t__) ; 
 char* dt_getstrattr (char*,char**) ; 
 int /*<<< orphan*/  dtrace_class_name (scalar_t__) ; 
 int /*<<< orphan*/  dtrace_stability_name (scalar_t__) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

int
dtrace_str2attr(const char *str, dtrace_attribute_t *attr)
{
	dtrace_stability_t s;
	dtrace_class_t c;
	char *p, *q;

	if (str == NULL || attr == NULL)
		return (-1); /* invalid function arguments */

	*attr = _dtrace_maxattr;
	p = alloca(strlen(str) + 1);
	(void) strcpy(p, str);

	if ((p = dt_getstrattr(p, &q)) == NULL)
		return (0);

	for (s = 0; s <= DTRACE_STABILITY_MAX; s++) {
		if (strcasecmp(p, dtrace_stability_name(s)) == 0) {
			attr->dtat_name = s;
			break;
		}
	}

	if (s > DTRACE_STABILITY_MAX)
		return (-1);

	if ((p = dt_getstrattr(q, &q)) == NULL)
		return (0);

	for (s = 0; s <= DTRACE_STABILITY_MAX; s++) {
		if (strcasecmp(p, dtrace_stability_name(s)) == 0) {
			attr->dtat_data = s;
			break;
		}
	}

	if (s > DTRACE_STABILITY_MAX)
		return (-1);

	if ((p = dt_getstrattr(q, &q)) == NULL)
		return (0);

	for (c = 0; c <= DTRACE_CLASS_MAX; c++) {
		if (strcasecmp(p, dtrace_class_name(c)) == 0) {
			attr->dtat_class = c;
			break;
		}
	}

	if (c > DTRACE_CLASS_MAX || (p = dt_getstrattr(q, &q)) != NULL)
		return (-1);

	return (0);
}