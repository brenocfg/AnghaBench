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
 scalar_t__ fopen (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftyp ; 
 scalar_t__ fvalue ; 

__attribute__((used)) static int
ffunc(char *fnam)
{
	fvalue = fopen (fnam,ftyp);
	return (fvalue == 0);
}