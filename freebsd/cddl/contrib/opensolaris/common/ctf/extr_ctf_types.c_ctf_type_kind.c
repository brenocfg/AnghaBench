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
struct TYPE_3__ {int /*<<< orphan*/  ctt_info; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 int CTF_ERR ; 
 int LCTF_INFO_KIND (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctf_lookup_by_id (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int
ctf_type_kind(ctf_file_t *fp, ctf_id_t type)
{
	const ctf_type_t *tp;

	if ((tp = ctf_lookup_by_id(&fp, type)) == NULL)
		return (CTF_ERR); /* errno is set for us */

	return (LCTF_INFO_KIND(fp, tp->ctt_info));
}