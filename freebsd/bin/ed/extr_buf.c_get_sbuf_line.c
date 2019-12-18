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
struct TYPE_4__ {scalar_t__ seek; size_t len; } ;
typedef  TYPE_1__ line_t ;

/* Variables and functions */
 int /*<<< orphan*/  REALLOC (char*,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 TYPE_1__ buffer_head ; 
 char* errmsg ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ fseeko (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int seek_write ; 
 int /*<<< orphan*/  sfp ; 
 scalar_t__ sfseek ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

char *
get_sbuf_line(line_t *lp)
{
	static char *sfbuf = NULL;	/* buffer */
	static size_t sfbufsz;		/* buffer size */

	size_t len;

	if (lp == &buffer_head)
		return NULL;
	seek_write = 1;				/* force seek on write */
	/* out of position */
	if (sfseek != lp->seek) {
		sfseek = lp->seek;
		if (fseeko(sfp, sfseek, SEEK_SET) < 0) {
			fprintf(stderr, "%s\n", strerror(errno));
			errmsg = "cannot seek temp file";
			return NULL;
		}
	}
	len = lp->len;
	REALLOC(sfbuf, sfbufsz, len + 1, NULL);
	if (fread(sfbuf, sizeof(char), len, sfp) != len) {
		fprintf(stderr, "%s\n", strerror(errno));
		errmsg = "cannot read temp file";
		return NULL;
	}
	sfseek += len;				/* update file position */
	sfbuf[len] = '\0';
	return sfbuf;
}