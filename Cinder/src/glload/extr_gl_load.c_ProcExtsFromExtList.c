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
typedef  scalar_t__ GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_NUM_EXTENSIONS ; 
 int /*<<< orphan*/  LoadExtByName (char const*) ; 
 int /*<<< orphan*/  _funcptr_glGetIntegerv (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ _funcptr_glGetStringi (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ProcExtsFromExtList()
{
	GLint iLoop;
	GLint iNumExtensions = 0;
	_funcptr_glGetIntegerv(GL_NUM_EXTENSIONS, &iNumExtensions);

	for(iLoop = 0; iLoop < iNumExtensions; iLoop++)
	{
		const char *strExtensionName = (const char *)_funcptr_glGetStringi(GL_EXTENSIONS, iLoop);
		LoadExtByName(strExtensionName);
	}
}