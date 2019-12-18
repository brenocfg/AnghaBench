#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  format ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {char* pfc_name; int /*<<< orphan*/  pfc_ofmt; } ;
typedef  TYPE_1__ dt_pfconv_t ;
struct TYPE_5__ {int pfv_argc; int /*<<< orphan*/  pfv_format; TYPE_3__* pfv_argv; } ;
typedef  TYPE_2__ dt_pfargv_t ;
struct TYPE_6__ {int pfd_width; int pfd_prec; int pfd_preflen; int pfd_flags; char* pfd_fmt; int /*<<< orphan*/ * pfd_prefix; TYPE_1__* pfd_conv; struct TYPE_6__* pfd_next; } ;
typedef  TYPE_3__ dt_pfargd_t ;

/* Variables and functions */
 int DT_PFCONV_AGG ; 
 int DT_PFCONV_ALT ; 
 int DT_PFCONV_DYNPREC ; 
 int DT_PFCONV_DYNWIDTH ; 
 int DT_PFCONV_GROUP ; 
 int DT_PFCONV_LEFT ; 
 int DT_PFCONV_SPACE ; 
 int DT_PFCONV_SPOS ; 
 int DT_PFCONV_ZPAD ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

size_t
dtrace_printf_format(dtrace_hdl_t *dtp, void *fmtdata, char *s, size_t len)
{
	dt_pfargv_t *pfv = fmtdata;
	dt_pfargd_t *pfd = pfv->pfv_argv;

	/*
	 * An upper bound on the string length is the length of the original
	 * format string, plus three times the number of conversions (each
	 * conversion could add up an additional "ll" and/or pfd_width digit
	 * in the case of converting %? to %16) plus one for a terminating \0.
	 */
	size_t formatlen = strlen(pfv->pfv_format) + 3 * pfv->pfv_argc + 1;
	char *format = alloca(formatlen);
	char *f = format;
	int i, j;

	for (i = 0; i < pfv->pfv_argc; i++, pfd = pfd->pfd_next) {
		const dt_pfconv_t *pfc = pfd->pfd_conv;
		const char *str;
		int width = pfd->pfd_width;
		int prec = pfd->pfd_prec;

		if (pfd->pfd_preflen != 0) {
			for (j = 0; j < pfd->pfd_preflen; j++)
				*f++ = pfd->pfd_prefix[j];
		}

		if (pfc == NULL)
			continue;

		*f++ = '%';

		if (pfd->pfd_flags & DT_PFCONV_ALT)
			*f++ = '#';
		if (pfd->pfd_flags & DT_PFCONV_ZPAD)
			*f++ = '0';
		if (pfd->pfd_flags & DT_PFCONV_LEFT)
			*f++ = '-';
		if (pfd->pfd_flags & DT_PFCONV_SPOS)
			*f++ = '+';
		if (pfd->pfd_flags & DT_PFCONV_DYNWIDTH)
			*f++ = '*';
		if (pfd->pfd_flags & DT_PFCONV_DYNPREC) {
			*f++ = '.';
			*f++ = '*';
		}
		if (pfd->pfd_flags & DT_PFCONV_GROUP)
			*f++ = '\'';
		if (pfd->pfd_flags & DT_PFCONV_SPACE)
			*f++ = ' ';
		if (pfd->pfd_flags & DT_PFCONV_AGG)
			*f++ = '@';

		if (width != 0)
			f += snprintf(f, sizeof (format), "%d", width);

		if (prec != 0)
			f += snprintf(f, sizeof (format), ".%d", prec);

		/*
		 * If the output format is %s, then either %s is the underlying
		 * conversion or the conversion is one of our customized ones,
		 * e.g. pfprint_addr.  In these cases, put the original string
		 * name of the conversion (pfc_name) into the pickled format
		 * string rather than the derived conversion (pfd_fmt).
		 */
		if (strcmp(pfc->pfc_ofmt, "s") == 0)
			str = pfc->pfc_name;
		else
			str = pfd->pfd_fmt;

		for (j = 0; str[j] != '\0'; j++)
			*f++ = str[j];
	}

	*f = '\0'; /* insert nul byte; do not count in return value */

	assert(f < format + formatlen);
	(void) strncpy(s, format, len);

	return ((size_t)(f - format));
}