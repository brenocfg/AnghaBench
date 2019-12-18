#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ dbcnt; scalar_t__ dbp; } ;
struct TYPE_5__ {int /*<<< orphan*/  dbcnt; scalar_t__ dbp; } ;
struct TYPE_4__ {int /*<<< orphan*/  trunc; } ;

/* Variables and functions */
 scalar_t__ cbsz ; 
 char* ctab ; 
 TYPE_3__ in ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,char,scalar_t__) ; 
 TYPE_2__ out ; 
 TYPE_1__ st ; 

void
block_close(void)
{
	/*
	 * Copy any remaining data into the output buffer and pad to a record.
	 * Don't worry about truncation or translation, the input buffer is
	 * always empty when truncating, and no characters have been added for
	 * translation.  The bottom line is that anything left in the input
	 * buffer is a truncated record.  Anything left in the output buffer
	 * just wasn't big enough.
	 */
	if (in.dbcnt) {
		++st.trunc;
		(void)memmove(out.dbp, in.dbp - in.dbcnt, in.dbcnt);
		(void)memset(out.dbp + in.dbcnt, ctab ? ctab[' '] : ' ',
		    cbsz - in.dbcnt);
		out.dbcnt += cbsz;
	}
}