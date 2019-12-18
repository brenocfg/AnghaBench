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
struct TYPE_3__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 char* PORTALFILE ; 
 int /*<<< orphan*/  WriteFaceFile_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WritePortalFile_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _printf (char*,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int num_solidfaces ; 
 int num_visclusters ; 
 int num_visportals ; 
 int /*<<< orphan*/  pf ; 
 int /*<<< orphan*/  qprintf (char*) ; 
 char* source ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void WritePortalFile (tree_t *tree)
{
	char	filename[1024];

	qprintf ("--- WritePortalFile ---\n");
	
	// write the file
	sprintf (filename, "%s.prt", source);
	_printf ("writing %s\n", filename);
	pf = fopen (filename, "w");
	if (!pf)
		Error ("Error opening %s", filename);
		
	fprintf (pf, "%s\n", PORTALFILE);
	fprintf (pf, "%i\n", num_visclusters);
	fprintf (pf, "%i\n", num_visportals);
	fprintf (pf, "%i\n", num_solidfaces);

	WritePortalFile_r(tree->headnode);
	WriteFaceFile_r(tree->headnode);

	fclose (pf);
}