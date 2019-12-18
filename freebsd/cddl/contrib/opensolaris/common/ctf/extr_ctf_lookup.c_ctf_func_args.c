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
typedef  int /*<<< orphan*/  ushort_t ;
typedef  size_t ulong_t ;
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  ctf_id_t ;
struct TYPE_6__ {int /*<<< orphan*/  ctc_argc; } ;
typedef  TYPE_1__ ctf_funcinfo_t ;
struct TYPE_7__ {scalar_t__* ctf_sxlate; scalar_t__ ctf_buf; } ;
typedef  TYPE_2__ ctf_file_t ;

/* Variables and functions */
 scalar_t__ CTF_ERR ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ctf_func_info (TYPE_2__*,size_t,TYPE_1__*) ; 

int
ctf_func_args(ctf_file_t *fp, ulong_t symidx, uint_t argc, ctf_id_t *argv)
{
	const ushort_t *dp;
	ctf_funcinfo_t f;

	if (ctf_func_info(fp, symidx, &f) == CTF_ERR)
		return (CTF_ERR); /* errno is set for us */

	/*
	 * The argument data is two ushort_t's past the translation table
	 * offset: one for the function info, and one for the return type.
	 */
	dp = (ushort_t *)((uintptr_t)fp->ctf_buf + fp->ctf_sxlate[symidx]) + 2;

	for (argc = MIN(argc, f.ctc_argc); argc != 0; argc--)
		*argv++ = *dp++;

	return (0);
}