#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_16__ {int /*<<< orphan*/  h_type; } ;
typedef  TYPE_3__ ctf_helem_t ;
typedef  int /*<<< orphan*/  ctf_hash_t ;
struct TYPE_17__ {TYPE_2__* ctf_dmodel; int /*<<< orphan*/  ctf_enums; } ;
typedef  TYPE_4__ ctf_file_t ;
struct TYPE_14__ {int /*<<< orphan*/  ctt_size; int /*<<< orphan*/  ctt_info; } ;
struct TYPE_18__ {TYPE_1__ dtd_data; } ;
typedef  TYPE_5__ ctf_dtdef_t ;
struct TYPE_15__ {int /*<<< orphan*/  ctd_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  CTF_K_ENUM ; 
 scalar_t__ CTF_K_FORWARD ; 
 int /*<<< orphan*/  CTF_TYPE_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_add_generic (TYPE_4__*,int /*<<< orphan*/ ,char const*,TYPE_5__**) ; 
 TYPE_5__* ctf_dtd_lookup (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ctf_hash_lookup (int /*<<< orphan*/ *,TYPE_4__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_type_kind (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

ctf_id_t
ctf_add_enum(ctf_file_t *fp, uint_t flag, const char *name)
{
	ctf_hash_t *hp = &fp->ctf_enums;
	ctf_helem_t *hep = NULL;
	ctf_dtdef_t *dtd;
	ctf_id_t type;

	if (name != NULL)
		hep = ctf_hash_lookup(hp, fp, name, strlen(name));

	if (hep != NULL && ctf_type_kind(fp, hep->h_type) == CTF_K_FORWARD)
		dtd = ctf_dtd_lookup(fp, type = hep->h_type);
	else if ((type = ctf_add_generic(fp, flag, name, &dtd)) == CTF_ERR)
		return (CTF_ERR); /* errno is set for us */

	dtd->dtd_data.ctt_info = CTF_TYPE_INFO(CTF_K_ENUM, flag, 0);
	dtd->dtd_data.ctt_size = fp->ctf_dmodel->ctd_int;

	return (type);
}