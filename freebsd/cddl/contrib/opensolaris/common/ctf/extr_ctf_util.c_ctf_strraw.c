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
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_4__ {char const* cts_strs; scalar_t__ cts_len; } ;
typedef  TYPE_1__ ctf_strs_t ;
struct TYPE_5__ {TYPE_1__* ctf_str; } ;
typedef  TYPE_2__ ctf_file_t ;

/* Variables and functions */
 int CTF_NAME_OFFSET (int /*<<< orphan*/ ) ; 
 size_t CTF_NAME_STID (int /*<<< orphan*/ ) ; 

const char *
ctf_strraw(ctf_file_t *fp, uint_t name)
{
	ctf_strs_t *ctsp = &fp->ctf_str[CTF_NAME_STID(name)];

	if (ctsp->cts_strs != NULL && CTF_NAME_OFFSET(name) < ctsp->cts_len)
		return (ctsp->cts_strs + CTF_NAME_OFFSET(name));

	/* string table not loaded or corrupt offset */
	return (NULL);
}