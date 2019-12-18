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
struct section {char* buf; size_t sz; int nocopy; int /*<<< orphan*/  name; } ;
struct sec_action {char* string; } ;
struct elfcopy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_append_section (struct elfcopy*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_compress_section (struct elfcopy*,int /*<<< orphan*/ ) ; 
 struct sec_action* lookup_sec_act (struct elfcopy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 char* read_section (struct section*,size_t*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

__attribute__((used)) static void
modify_section(struct elfcopy *ecp, struct section *s)
{
	struct sec_action	*sac;
	size_t			 srcsz, dstsz, p, len;
	char			*b, *c, *d, *src, *end;
	int			 dupe;

	src = read_section(s, &srcsz);
	if (src == NULL || srcsz == 0) {
		/* For empty section, we proceed if we need to append. */
		if (!is_append_section(ecp, s->name))
			return;
	}

	/* Allocate buffer needed for new section data. */
	dstsz = srcsz;
	if (is_append_section(ecp, s->name)) {
		sac = lookup_sec_act(ecp, s->name, 0);
		dstsz += strlen(sac->string) + 1;
	}
	if ((b = malloc(dstsz)) == NULL)
		err(EXIT_FAILURE, "malloc failed");
	s->buf = b;

	/* Compress section. */
	p = 0;
	if (is_compress_section(ecp, s->name)) {
		end = src + srcsz;
		for(c = src; c < end;) {
			len = 0;
			while(c + len < end && c[len] != '\0')
				len++;
			if (c + len == end) {
				/* XXX should we warn here? */
				strncpy(&b[p], c, len);
				p += len;
				break;
			}
			dupe = 0;
			for (d = b; d < b + p; ) {
				if (strcmp(d, c) == 0) {
					dupe = 1;
					break;
				}
				d += strlen(d) + 1;
			}
			if (!dupe) {
				strncpy(&b[p], c, len);
				b[p + len] = '\0';
				p += len + 1;
			}
			c += len + 1;
		}
	} else {
		memcpy(b, src, srcsz);
		p += srcsz;
	}

	/* Append section. */
	if (is_append_section(ecp, s->name)) {
		sac = lookup_sec_act(ecp, s->name, 0);
		len = strlen(sac->string);
		strncpy(&b[p], sac->string, len);
		b[p + len] = '\0';
		p += len + 1;
	}

	s->sz = p;
	s->nocopy = 1;
}