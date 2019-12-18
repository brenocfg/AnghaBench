#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int /*<<< orphan*/  ctt_info; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_7__ {int /*<<< orphan*/  cte_bits; int /*<<< orphan*/  cte_offset; int /*<<< orphan*/  cte_format; } ;
typedef  TYPE_2__ ctf_encoding_t ;

/* Variables and functions */
 int CTF_ERR ; 
 int /*<<< orphan*/  CTF_FP_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_FP_ENCODING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_FP_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_INT_BITS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_INT_ENCODING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTF_INT_OFFSET (int /*<<< orphan*/ ) ; 
#define  CTF_K_FLOAT 129 
#define  CTF_K_INTEGER 128 
 int /*<<< orphan*/  ECTF_NOTINTFP ; 
 int LCTF_INFO_KIND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctf_get_ctt_size (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* ctf_lookup_by_id (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
ctf_type_encoding(ctf_file_t *fp, ctf_id_t type, ctf_encoding_t *ep)
{
	ctf_file_t *ofp = fp;
	const ctf_type_t *tp;
	ssize_t increment;
	uint_t data;

	if ((tp = ctf_lookup_by_id(&fp, type)) == NULL)
		return (CTF_ERR); /* errno is set for us */

	(void) ctf_get_ctt_size(fp, tp, NULL, &increment);

	switch (LCTF_INFO_KIND(fp, tp->ctt_info)) {
	case CTF_K_INTEGER:
		data = *(const uint_t *)((uintptr_t)tp + increment);
		ep->cte_format = CTF_INT_ENCODING(data);
		ep->cte_offset = CTF_INT_OFFSET(data);
		ep->cte_bits = CTF_INT_BITS(data);
		break;
	case CTF_K_FLOAT:
		data = *(const uint_t *)((uintptr_t)tp + increment);
		ep->cte_format = CTF_FP_ENCODING(data);
		ep->cte_offset = CTF_FP_OFFSET(data);
		ep->cte_bits = CTF_FP_BITS(data);
		break;
	default:
		return (ctf_set_errno(ofp, ECTF_NOTINTFP));
	}

	return (0);
}