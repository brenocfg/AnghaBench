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
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_4__ {scalar_t__ st_size; } ;
struct TYPE_5__ {char* ln_name; size_t ln_nlen; TYPE_1__ sb; } ;
typedef  TYPE_2__ ARCHD ;

/* Variables and functions */
 int /*<<< orphan*/  paxwarn (int,char*,...) ; 
 int rd_wrbuf (char*,int) ; 

__attribute__((used)) static int
rd_ln_nm(ARCHD *arcn)
{
	/*
	 * check the length specified for bogus values
	 */
	if ((arcn->sb.st_size == 0) ||
	    ((size_t)arcn->sb.st_size >= sizeof(arcn->ln_name))) {
#		ifdef NET2_STAT
		paxwarn(1, "Cpio link name length is invalid: %lu",
		    arcn->sb.st_size);
#		else
		paxwarn(1, "Cpio link name length is invalid: %ju",
		    (uintmax_t)arcn->sb.st_size);
#		endif
		return(-1);
	}

	/*
	 * read in the link name and \0 terminate it
	 */
	if (rd_wrbuf(arcn->ln_name, (int)arcn->sb.st_size) !=
	    (int)arcn->sb.st_size) {
		paxwarn(1, "Cpio link name read error");
		return(-1);
	}
	arcn->ln_nlen = arcn->sb.st_size;
	arcn->ln_name[arcn->ln_nlen] = '\0';

	/*
	 * watch out for those empty link names
	 */
	if (arcn->ln_name[0] == '\0') {
		paxwarn(1, "Cpio link name is corrupt");
		return(-1);
	}
	return(0);
}