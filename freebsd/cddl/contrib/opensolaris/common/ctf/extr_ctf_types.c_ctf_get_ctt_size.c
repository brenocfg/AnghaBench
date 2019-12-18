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
typedef  int ssize_t ;
struct TYPE_6__ {scalar_t__ ctt_size; } ;
typedef  TYPE_1__ ctf_type_t ;
typedef  int /*<<< orphan*/  ctf_stype_t ;
struct TYPE_7__ {scalar_t__ ctf_version; } ;
typedef  TYPE_2__ ctf_file_t ;

/* Variables and functions */
 scalar_t__ CTF_LSIZE_SENT ; 
 int CTF_TYPE_LSIZE (TYPE_1__ const*) ; 
 scalar_t__ CTF_VERSION_1 ; 

ssize_t
ctf_get_ctt_size(const ctf_file_t *fp, const ctf_type_t *tp, ssize_t *sizep,
    ssize_t *incrementp)
{
	ssize_t size, increment;

	if (fp->ctf_version > CTF_VERSION_1 &&
	    tp->ctt_size == CTF_LSIZE_SENT) {
		size = CTF_TYPE_LSIZE(tp);
		increment = sizeof (ctf_type_t);
	} else {
		size = tp->ctt_size;
		increment = sizeof (ctf_stype_t);
	}

	if (sizep)
		*sizep = size;
	if (incrementp)
		*incrementp = increment;

	return (size);
}