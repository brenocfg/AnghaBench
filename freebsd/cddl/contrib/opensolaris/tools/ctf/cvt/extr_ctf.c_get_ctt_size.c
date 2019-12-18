#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t ctt_size; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_stype_t ;

/* Variables and functions */
 size_t CTF_LSIZE_SENT ; 
 scalar_t__ CTF_TYPE_LSIZE (TYPE_1__*) ; 

__attribute__((used)) static void
get_ctt_size(ctf_type_t *ctt, size_t *sizep, size_t *incrementp)
{
	if (ctt->ctt_size == CTF_LSIZE_SENT) {
		*sizep = (size_t)CTF_TYPE_LSIZE(ctt);
		*incrementp = sizeof (ctf_type_t);
	} else {
		*sizep = ctt->ctt_size;
		*incrementp = sizeof (ctf_stype_t);
	}
}