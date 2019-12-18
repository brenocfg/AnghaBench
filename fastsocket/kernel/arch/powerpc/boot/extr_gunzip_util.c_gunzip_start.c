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
struct TYPE_2__ {int total_in; int avail_in; void* next_in; int /*<<< orphan*/  workspace; } ;
struct gunzip_state {TYPE_1__ s; int /*<<< orphan*/  scratch; } ;

/* Variables and functions */
 int COMMENT ; 
 int EXTRA_FIELD ; 
 int HEAD_CRC ; 
 int /*<<< orphan*/  MAX_WBITS ; 
 int ORIG_NAME ; 
 int RESERVED ; 
 char Z_DEFLATED ; 
 int Z_OK ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  memset (struct gunzip_state*,int /*<<< orphan*/ ,int) ; 
 int zlib_inflateInit2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int zlib_inflate_workspacesize () ; 

void gunzip_start(struct gunzip_state *state, void *src, int srclen)
{
	char *hdr = src;
	int hdrlen = 0;

	memset(state, 0, sizeof(*state));

	/* Check for gzip magic number */
	if ((hdr[0] == 0x1f) && (hdr[1] == 0x8b)) {
		/* gzip data, initialize zlib parameters */
		int r, flags;

		state->s.workspace = state->scratch;
		if (zlib_inflate_workspacesize() > sizeof(state->scratch))
			fatal("insufficient scratch space for gunzip\n\r");

		/* skip header */
		hdrlen = 10;
		flags = hdr[3];
		if (hdr[2] != Z_DEFLATED || (flags & RESERVED) != 0)
			fatal("bad gzipped data\n\r");
		if ((flags & EXTRA_FIELD) != 0)
			hdrlen = 12 + hdr[10] + (hdr[11] << 8);
		if ((flags & ORIG_NAME) != 0)
			while (hdr[hdrlen++] != 0)
				;
		if ((flags & COMMENT) != 0)
			while (hdr[hdrlen++] != 0)
				;
		if ((flags & HEAD_CRC) != 0)
			hdrlen += 2;
		if (hdrlen >= srclen)
			fatal("gunzip_start: ran out of data in header\n\r");

		r = zlib_inflateInit2(&state->s, -MAX_WBITS);
		if (r != Z_OK)
			fatal("inflateInit2 returned %d\n\r", r);
	}

	state->s.total_in = hdrlen;
	state->s.next_in = src + hdrlen;
	state->s.avail_in = srclen - hdrlen;
}