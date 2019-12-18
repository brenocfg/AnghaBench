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
struct TYPE_3__ {int /*<<< orphan*/  ctt_type; int /*<<< orphan*/  ctt_info; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
#define  CTF_K_CONST 131 
#define  CTF_K_RESTRICT 130 
#define  CTF_K_TYPEDEF 129 
#define  CTF_K_VOLATILE 128 
 int /*<<< orphan*/  ECTF_CORRUPT ; 
 int LCTF_INFO_KIND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_dprintf (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctf_lookup_by_id (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ctf_id_t
ctf_type_resolve(ctf_file_t *fp, ctf_id_t type)
{
	ctf_id_t prev = type, otype = type;
	ctf_file_t *ofp = fp;
	const ctf_type_t *tp;

	while ((tp = ctf_lookup_by_id(&fp, type)) != NULL) {
		switch (LCTF_INFO_KIND(fp, tp->ctt_info)) {
		case CTF_K_TYPEDEF:
		case CTF_K_VOLATILE:
		case CTF_K_CONST:
		case CTF_K_RESTRICT:
			if (tp->ctt_type == type || tp->ctt_type == otype ||
			    tp->ctt_type == prev) {
				ctf_dprintf("type %ld cycle detected\n", otype);
				return (ctf_set_errno(ofp, ECTF_CORRUPT));
			}
			prev = type;
			type = tp->ctt_type;
			break;
		default:
			return (type);
		}
	}

	return (CTF_ERR); /* errno is set for us */
}