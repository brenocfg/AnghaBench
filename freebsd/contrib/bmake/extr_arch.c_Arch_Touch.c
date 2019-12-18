#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ar_hdr {int /*<<< orphan*/  AR_DATE; } ;
typedef  int /*<<< orphan*/  GNode ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ARCHIVE ; 
 int /*<<< orphan*/ * ArchFindMember (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ar_hdr*,char*) ; 
 int /*<<< orphan*/  MEMBER ; 
 int /*<<< orphan*/  Var_Value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ now ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,long) ; 

void
Arch_Touch(GNode *gn)
{
    FILE *	  arch;	  /* Stream open to archive, positioned properly */
    struct ar_hdr arh;	  /* Current header describing member */
    char *p1, *p2;

    arch = ArchFindMember(Var_Value(ARCHIVE, gn, &p1),
			  Var_Value(MEMBER, gn, &p2),
			  &arh, "r+");

    free(p1);
    free(p2);

    snprintf(arh.AR_DATE, sizeof(arh.AR_DATE), "%-12ld", (long) now);

    if (arch != NULL) {
	(void)fwrite((char *)&arh, sizeof(struct ar_hdr), 1, arch);
	fclose(arch);
    }
}