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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ffunc ; 
 char const* ftyp ; 
 int /*<<< orphan*/ * fvalue ; 
 scalar_t__ searchp (char const*,char*,char*,int /*<<< orphan*/ ) ; 

FILE *
fopenp(const char *fpath, char *file, char *complete, const char *ftype)
{
	ftyp = ftype;
	if (searchp(fpath,file,complete,ffunc) < 0)  return (0);
	return (fvalue);
}