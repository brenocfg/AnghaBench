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

/* Variables and functions */
 int flgs ; 
 int /*<<< orphan*/  func ; 
 int mod ; 
 scalar_t__ searchp (char const*,char*,char*,int /*<<< orphan*/ ) ; 
 int value ; 

int
openp(const char *fpath, char *file, char *complete, int flags, int mode)
{
	flgs = flags;
	mod = mode;
	if (searchp(fpath,file,complete,func) < 0)  return (-1);
	return (value);
}