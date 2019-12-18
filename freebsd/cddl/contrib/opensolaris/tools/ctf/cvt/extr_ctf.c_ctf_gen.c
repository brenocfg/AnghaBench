#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int iib_nobjts; int iib_nfuncs; int /*<<< orphan*/  iib_types; int /*<<< orphan*/ * iib_funcs; int /*<<< orphan*/ * iib_objts; TYPE_1__* iib_td; } ;
typedef  TYPE_3__ iiburst_t ;
struct TYPE_19__ {int /*<<< orphan*/  ctp_magic; } ;
struct TYPE_21__ {void* cth_strlen; void* cth_stroff; void* cth_typeoff; void* cth_funcoff; void* cth_objtoff; void* cth_lbloff; void* cth_parname; void* cth_parlabel; TYPE_2__ cth_preamble; int /*<<< orphan*/  cth_flags; int /*<<< orphan*/  cth_version; int /*<<< orphan*/  cth_magic; } ;
typedef  TYPE_4__ ctf_header_t ;
struct TYPE_22__ {int /*<<< orphan*/  ctb_strtab; } ;
typedef  TYPE_5__ ctf_buf_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_18__ {int /*<<< orphan*/  td_labels; int /*<<< orphan*/  td_parname; int /*<<< orphan*/  td_parlabel; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_F_COMPRESS ; 
 int /*<<< orphan*/  CTF_MAGIC ; 
 int CTF_SWAP_BYTES ; 
 int /*<<< orphan*/  CTF_VERSION ; 
 int /*<<< orphan*/  SWAP_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP_32 (void*) ; 
 void* ctf_buf_cur (TYPE_5__*) ; 
 int /*<<< orphan*/  ctf_buf_free (TYPE_5__*) ; 
 TYPE_5__* ctf_buf_new () ; 
 int /*<<< orphan*/  debug (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  pad_buffer (TYPE_5__*,int) ; 
 void* strtab_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* strtab_size (int /*<<< orphan*/ *) ; 
 int target_requires_swap ; 
 int /*<<< orphan*/  write_buffer (TYPE_4__*,TYPE_5__*,size_t*) ; 
 int /*<<< orphan*/  write_compressed_buffer (TYPE_4__*,TYPE_5__*,size_t*) ; 
 int /*<<< orphan*/  write_functions (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  write_label ; 
 int /*<<< orphan*/  write_objects (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  write_type ; 

caddr_t
ctf_gen(iiburst_t *iiburst, size_t *resszp, int do_compress)
{
	ctf_buf_t *buf = ctf_buf_new();
	ctf_header_t h;
	caddr_t outbuf;

	int i;

	target_requires_swap = do_compress & CTF_SWAP_BYTES;
	do_compress &= ~CTF_SWAP_BYTES;

	/*
	 * Prepare the header, and create the CTF output buffers.  The data
	 * object section and function section are both lists of 2-byte
	 * integers; we pad these out to the next 4-byte boundary if needed.
	 */
	h.cth_magic = CTF_MAGIC;
	h.cth_version = CTF_VERSION;
	h.cth_flags = do_compress ? CTF_F_COMPRESS : 0;
	h.cth_parlabel = strtab_insert(&buf->ctb_strtab,
	    iiburst->iib_td->td_parlabel);
	h.cth_parname = strtab_insert(&buf->ctb_strtab,
	    iiburst->iib_td->td_parname);

	h.cth_lbloff = 0;
	(void) list_iter(iiburst->iib_td->td_labels, write_label,
	    buf);

	pad_buffer(buf, 2);
	h.cth_objtoff = ctf_buf_cur(buf);
	for (i = 0; i < iiburst->iib_nobjts; i++)
		write_objects(iiburst->iib_objts[i], buf);

	pad_buffer(buf, 2);
	h.cth_funcoff = ctf_buf_cur(buf);
	for (i = 0; i < iiburst->iib_nfuncs; i++)
		write_functions(iiburst->iib_funcs[i], buf);

	pad_buffer(buf, 4);
	h.cth_typeoff = ctf_buf_cur(buf);
	(void) list_iter(iiburst->iib_types, write_type, buf);

	debug(2, "CTF wrote %d types\n", list_count(iiburst->iib_types));

	h.cth_stroff = ctf_buf_cur(buf);
	h.cth_strlen = strtab_size(&buf->ctb_strtab);

	if (target_requires_swap) {
		SWAP_16(h.cth_preamble.ctp_magic);
		SWAP_32(h.cth_parlabel);
		SWAP_32(h.cth_parname);
		SWAP_32(h.cth_lbloff);
		SWAP_32(h.cth_objtoff);
		SWAP_32(h.cth_funcoff);
		SWAP_32(h.cth_typeoff);
		SWAP_32(h.cth_stroff);
		SWAP_32(h.cth_strlen);
	}

	/*
	 * We only do compression for ctfmerge, as ctfconvert is only
	 * supposed to be used on intermediary build objects. This is
	 * significantly faster.
	 */
	if (do_compress)
		outbuf = write_compressed_buffer(&h, buf, resszp);
	else
		outbuf = write_buffer(&h, buf, resszp);

	ctf_buf_free(buf);
	return (outbuf);
}