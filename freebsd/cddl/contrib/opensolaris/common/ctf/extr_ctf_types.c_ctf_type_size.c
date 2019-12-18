#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_15__ {int /*<<< orphan*/  ctt_info; } ;
typedef  TYPE_2__ ctf_type_t ;
typedef  int ctf_id_t ;
struct TYPE_16__ {TYPE_1__* ctf_dmodel; } ;
typedef  TYPE_3__ ctf_file_t ;
struct TYPE_17__ {int ctr_contents; int ctr_nelems; } ;
typedef  TYPE_4__ ctf_arinfo_t ;
struct TYPE_14__ {int ctd_pointer; int ctd_int; } ;

/* Variables and functions */
 int CTF_ERR ; 
#define  CTF_K_ARRAY 131 
#define  CTF_K_ENUM 130 
#define  CTF_K_FUNCTION 129 
#define  CTF_K_POINTER 128 
 int LCTF_INFO_KIND (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ctf_array_info (TYPE_3__*,int,TYPE_4__*) ; 
 int ctf_get_ctt_size (TYPE_3__*,TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* ctf_lookup_by_id (TYPE_3__**,int) ; 
 int ctf_type_resolve (TYPE_3__*,int) ; 

ssize_t
ctf_type_size(ctf_file_t *fp, ctf_id_t type)
{
	const ctf_type_t *tp;
	ssize_t size;
	ctf_arinfo_t ar;

	if ((type = ctf_type_resolve(fp, type)) == CTF_ERR)
		return (-1); /* errno is set for us */

	if ((tp = ctf_lookup_by_id(&fp, type)) == NULL)
		return (-1); /* errno is set for us */

	switch (LCTF_INFO_KIND(fp, tp->ctt_info)) {
	case CTF_K_POINTER:
		return (fp->ctf_dmodel->ctd_pointer);

	case CTF_K_FUNCTION:
		return (0); /* function size is only known by symtab */

	case CTF_K_ENUM:
		return (fp->ctf_dmodel->ctd_int);

	case CTF_K_ARRAY:
		/*
		 * Array size is not directly returned by stabs data.  Instead,
		 * it defines the element type and requires the user to perform
		 * the multiplication.  If ctf_get_ctt_size() returns zero, the
		 * current version of ctfconvert does not compute member sizes
		 * and we compute the size here on its behalf.
		 */
		if ((size = ctf_get_ctt_size(fp, tp, NULL, NULL)) > 0)
			return (size);

		if (ctf_array_info(fp, type, &ar) == CTF_ERR ||
		    (size = ctf_type_size(fp, ar.ctr_contents)) == CTF_ERR)
			return (-1); /* errno is set for us */

		return (size * ar.ctr_nelems);

	default:
		return (ctf_get_ctt_size(fp, tp, NULL, NULL));
	}
}