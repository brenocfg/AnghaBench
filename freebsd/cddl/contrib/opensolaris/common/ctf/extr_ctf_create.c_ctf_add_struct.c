#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_14__ {int /*<<< orphan*/  h_type; } ;
typedef  TYPE_2__ ctf_helem_t ;
typedef  int /*<<< orphan*/  ctf_hash_t ;
struct TYPE_15__ {int /*<<< orphan*/  ctf_structs; } ;
typedef  TYPE_3__ ctf_file_t ;
struct TYPE_13__ {scalar_t__ ctt_size; int /*<<< orphan*/  ctt_info; } ;
struct TYPE_16__ {TYPE_1__ dtd_data; } ;
typedef  TYPE_4__ ctf_dtdef_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 scalar_t__ CTF_K_FORWARD ; 
 int /*<<< orphan*/  CTF_K_STRUCT ; 
 int /*<<< orphan*/  CTF_TYPE_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_add_generic (TYPE_3__*,int /*<<< orphan*/ ,char const*,TYPE_4__**) ; 
 TYPE_4__* ctf_dtd_lookup (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ctf_hash_lookup (int /*<<< orphan*/ *,TYPE_3__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_type_kind (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

ctf_id_t
ctf_add_struct(ctf_file_t *fp, uint_t flag, const char *name)
{
	ctf_hash_t *hp = &fp->ctf_structs;
	ctf_helem_t *hep = NULL;
	ctf_dtdef_t *dtd;
	ctf_id_t type;

	if (name != NULL)
		hep = ctf_hash_lookup(hp, fp, name, strlen(name));

	if (hep != NULL && ctf_type_kind(fp, hep->h_type) == CTF_K_FORWARD)
		dtd = ctf_dtd_lookup(fp, type = hep->h_type);
	else if ((type = ctf_add_generic(fp, flag, name, &dtd)) == CTF_ERR)
		return (CTF_ERR); /* errno is set for us */

	dtd->dtd_data.ctt_info = CTF_TYPE_INFO(CTF_K_STRUCT, flag, 0);
	dtd->dtd_data.ctt_size = 0;

	return (type);
}