#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_9__ {int /*<<< orphan*/  cte_bits; } ;
typedef  TYPE_3__ ctf_encoding_t ;
struct TYPE_7__ {TYPE_3__ dtu_enc; } ;
struct TYPE_8__ {int /*<<< orphan*/  ctt_size; int /*<<< orphan*/  ctt_info; } ;
struct TYPE_10__ {TYPE_1__ dtd_u; TYPE_2__ dtd_data; } ;
typedef  TYPE_4__ ctf_dtdef_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTF_ERR ; 
 int /*<<< orphan*/  CTF_TYPE_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int NBBY ; 
 int P2ROUNDUP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clp2 (int) ; 
 int /*<<< orphan*/  ctf_add_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,TYPE_4__**) ; 
 int /*<<< orphan*/  ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ctf_id_t
ctf_add_encoded(ctf_file_t *fp, uint_t flag,
    const char *name, const ctf_encoding_t *ep, uint_t kind)
{
	ctf_dtdef_t *dtd;
	ctf_id_t type;

	if (ep == NULL)
		return (ctf_set_errno(fp, EINVAL));

	if ((type = ctf_add_generic(fp, flag, name, &dtd)) == CTF_ERR)
		return (CTF_ERR); /* errno is set for us */

	dtd->dtd_data.ctt_info = CTF_TYPE_INFO(kind, flag, 0);
	dtd->dtd_data.ctt_size = clp2(P2ROUNDUP(ep->cte_bits, NBBY) / NBBY);
	dtd->dtd_u.dtu_enc = *ep;

	return (type);
}