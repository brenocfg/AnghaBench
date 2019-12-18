#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort_t ;
typedef  int /*<<< orphan*/  uint_t ;
typedef  scalar_t__ ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_4__ {scalar_t__ ctt_type; int /*<<< orphan*/  ctt_info; } ;
struct TYPE_5__ {TYPE_1__ dtd_data; } ;
typedef  TYPE_2__ ctf_dtdef_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 scalar_t__ CTF_MAX_TYPE ; 
 int /*<<< orphan*/  CTF_TYPE_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ ctf_add_generic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  ctf_ref_inc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ctf_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ctf_id_t
ctf_add_reftype(ctf_file_t *fp, uint_t flag, ctf_id_t ref, uint_t kind)
{
	ctf_dtdef_t *dtd;
	ctf_id_t type;

	if (ref == CTF_ERR || ref < 0 || ref > CTF_MAX_TYPE)
		return (ctf_set_errno(fp, EINVAL));

	if ((type = ctf_add_generic(fp, flag, NULL, &dtd)) == CTF_ERR)
		return (CTF_ERR); /* errno is set for us */

	ctf_ref_inc(fp, ref);

	dtd->dtd_data.ctt_info = CTF_TYPE_INFO(kind, flag, 0);
	dtd->dtd_data.ctt_type = (ushort_t)ref;

	return (type);
}