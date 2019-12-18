#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* dt_errmsg; scalar_t__ dt_ctferr; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
struct TYPE_5__ {int err; char const* msg; } ;

/* Variables and functions */
 int EDT_BASE ; 
 int EDT_COMPILER ; 
 int EDT_CTF ; 
 TYPE_3__* _dt_errlist ; 
 int _dt_nerr ; 
 char* ctf_errmsg (scalar_t__) ; 
 char* strerror (int) ; 

const char *
dtrace_errmsg(dtrace_hdl_t *dtp, int error)
{
	const char *str;
	int i;

	if (error == EDT_COMPILER && dtp != NULL && dtp->dt_errmsg[0] != '\0')
		str = dtp->dt_errmsg;
	else if (error == EDT_CTF && dtp != NULL && dtp->dt_ctferr != 0)
		str = ctf_errmsg(dtp->dt_ctferr);
	else if (error >= EDT_BASE && (error - EDT_BASE) < _dt_nerr) {
		for (i = 0; i < _dt_nerr; i++) {
			if (_dt_errlist[i].err == error)
				return (_dt_errlist[i].msg);
		}
		str = NULL;
	} else
		str = strerror(error);

	return (str ? str : "Unknown error");
}