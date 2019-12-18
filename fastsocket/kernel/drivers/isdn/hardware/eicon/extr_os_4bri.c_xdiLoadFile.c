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
typedef  scalar_t__ dword ;

/* Variables and functions */
 int /*<<< orphan*/ * diva_xdiLoadFileFile ; 
 scalar_t__ diva_xdiLoadFileLength ; 

void *xdiLoadFile(char *FileName, dword *FileLength,
		  unsigned long lim)
{
	void *ret = diva_xdiLoadFileFile;

	if (FileLength) {
		*FileLength = diva_xdiLoadFileLength;
	}
	diva_xdiLoadFileFile = NULL;
	diva_xdiLoadFileLength = 0;

	return (ret);
}