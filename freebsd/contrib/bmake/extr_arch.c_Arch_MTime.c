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
typedef  scalar_t__ time_t ;
struct ar_hdr {int /*<<< orphan*/  AR_DATE; } ;
struct TYPE_4__ {scalar_t__ mtime; } ;
typedef  TYPE_1__ GNode ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 struct ar_hdr* ArchStatMember (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMBER ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  Var_Value (int /*<<< orphan*/ ,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

time_t
Arch_MTime(GNode *gn)
{
    struct ar_hdr *arhPtr;    /* Header of desired member */
    time_t	  modTime;    /* Modification time as an integer */
    char *p1, *p2;

    arhPtr = ArchStatMember(Var_Value(ARCHIVE, gn, &p1),
			     Var_Value(MEMBER, gn, &p2),
			     TRUE);

    free(p1);
    free(p2);

    if (arhPtr != NULL) {
	modTime = (time_t)strtol(arhPtr->AR_DATE, NULL, 10);
    } else {
	modTime = 0;
    }

    gn->mtime = modTime;
    return (modTime);
}