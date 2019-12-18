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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*,char*) ; 
 int /*<<< orphan*/  WriteGLView_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _printf (char*,char*) ; 
 char* c_glfaces ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* outbase ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 

void WriteGLView (tree_t *tree, char *source)
{
	char	name[1024];
	FILE	*glview;

	c_glfaces = 0;
	sprintf (name, "%s%s.gl",outbase, source);
	_printf ("Writing %s\n", name);

	glview = fopen (name, "w");
	if (!glview)
		Error ("Couldn't open %s", name);
	WriteGLView_r (tree->headnode, glview);
	fclose (glview);

	_printf ("%5i c_glfaces\n", c_glfaces);
}