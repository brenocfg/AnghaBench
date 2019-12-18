#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tdata_t ;
typedef  int /*<<< orphan*/  symit_data_t ;
struct TYPE_3__ {scalar_t__ cth_magic; scalar_t__ cth_version; size_t cth_stroff; size_t cth_strlen; int cth_flags; } ;
typedef  TYPE_1__ ctf_header_t ;
typedef  int caddr_t ;

/* Variables and functions */
 int CTF_F_COMPRESS ; 
 scalar_t__ CTF_MAGIC ; 
 scalar_t__ CTF_VERSION ; 
 int /*<<< orphan*/ * ctf_parse (TYPE_1__*,int,int /*<<< orphan*/ *,char*) ; 
 char* curfile ; 
 size_t decompress_ctf (int,size_t,int,size_t) ; 
 int /*<<< orphan*/  free (int) ; 
 int /*<<< orphan*/  parseterminate (char*,...) ; 
 int xmalloc (size_t) ; 

tdata_t *
ctf_load(char *file, caddr_t buf, size_t bufsz, symit_data_t *si, char *label)
{
	ctf_header_t *h;
	caddr_t ctfdata;
	size_t ctfdatasz;
	tdata_t *td;

	curfile = file;

	if (bufsz < sizeof (ctf_header_t))
		parseterminate("Corrupt CTF - short header");

	void *v = (void *) buf;
	h = v;
	buf += sizeof (ctf_header_t);
	bufsz -= sizeof (ctf_header_t);

	if (h->cth_magic != CTF_MAGIC)
		parseterminate("Corrupt CTF - bad magic 0x%x", h->cth_magic);

	if (h->cth_version != CTF_VERSION)
		parseterminate("Unknown CTF version %d", h->cth_version);

	ctfdatasz = h->cth_stroff + h->cth_strlen;
	if (h->cth_flags & CTF_F_COMPRESS) {
		size_t actual;

		ctfdata = xmalloc(ctfdatasz);
		if ((actual = decompress_ctf(buf, bufsz, ctfdata, ctfdatasz)) !=
		    ctfdatasz) {
			parseterminate("Corrupt CTF - short decompression "
			    "(was %d, expecting %d)", actual, ctfdatasz);
		}
	} else {
		ctfdata = buf;
		ctfdatasz = bufsz;
	}

	td = ctf_parse(h, ctfdata, si, label);

	if (h->cth_flags & CTF_F_COMPRESS)
		free(ctfdata);

	curfile = NULL;

	return (td);
}