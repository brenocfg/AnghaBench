#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_12__ {int /*<<< orphan*/  h_type; } ;
typedef  TYPE_2__ ctf_helem_t ;
typedef  int /*<<< orphan*/  ctf_hash_t ;
struct TYPE_13__ {int /*<<< orphan*/  ctf_enums; int /*<<< orphan*/  ctf_unions; int /*<<< orphan*/  ctf_structs; } ;
typedef  TYPE_3__ ctf_file_t ;
struct TYPE_11__ {int ctt_type; int /*<<< orphan*/  ctt_info; } ;
struct TYPE_14__ {TYPE_1__ dtd_data; } ;
typedef  TYPE_4__ ctf_dtdef_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
#define  CTF_K_ENUM 130 
 int /*<<< orphan*/  CTF_K_FORWARD ; 
#define  CTF_K_STRUCT 129 
#define  CTF_K_UNION 128 
 int /*<<< orphan*/  CTF_TYPE_INFO (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ECTF_NOTSUE ; 
 int /*<<< orphan*/  ctf_add_generic (TYPE_3__*,int,char const*,TYPE_4__**) ; 
 TYPE_2__* ctf_hash_lookup (int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_set_errno (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

ctf_id_t
ctf_add_forward(ctf_file_t *fp, uint_t flag, const char *name, uint_t kind)
{
	ctf_hash_t *hp;
	ctf_helem_t *hep;
	ctf_dtdef_t *dtd;
	ctf_id_t type;

	switch (kind) {
	case CTF_K_STRUCT:
		hp = &fp->ctf_structs;
		break;
	case CTF_K_UNION:
		hp = &fp->ctf_unions;
		break;
	case CTF_K_ENUM:
		hp = &fp->ctf_enums;
		break;
	default:
		return (ctf_set_errno(fp, ECTF_NOTSUE));
	}

	/*
	 * If the type is already defined or exists as a forward tag, just
	 * return the ctf_id_t of the existing definition.
	 */
	if (name != NULL && (hep = ctf_hash_lookup(hp,
	    fp, name, strlen(name))) != NULL)
		return (hep->h_type);

	if ((type = ctf_add_generic(fp, flag, name, &dtd)) == CTF_ERR)
		return (CTF_ERR); /* errno is set for us */

	dtd->dtd_data.ctt_info = CTF_TYPE_INFO(CTF_K_FORWARD, flag, 0);
	dtd->dtd_data.ctt_type = kind;

	return (type);
}