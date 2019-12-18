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
typedef  int /*<<< orphan*/  ushort_t ;
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_3__ {int /*<<< orphan*/  h_type; } ;
typedef  TYPE_1__ ctf_helem_t ;
typedef  int /*<<< orphan*/  ctf_hash_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;

/* Variables and functions */
 int ctf_hash_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ctf_hash_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 char* ctf_strptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int
ctf_hash_define(ctf_hash_t *hp, ctf_file_t *fp, ushort_t type, uint_t name)
{
	const char *str = ctf_strptr(fp, name);
	ctf_helem_t *hep = ctf_hash_lookup(hp, fp, str, strlen(str));

	if (hep == NULL)
		return (ctf_hash_insert(hp, fp, type, name));

	hep->h_type = type;
	return (0);
}