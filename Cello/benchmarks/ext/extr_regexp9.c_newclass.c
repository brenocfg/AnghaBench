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
typedef  int /*<<< orphan*/  Reclass ;

/* Variables and functions */
 scalar_t__ NCLASS ; 
 int /*<<< orphan*/ * classp ; 
 scalar_t__ nclass ; 
 int /*<<< orphan*/  regerr2 (char*,scalar_t__) ; 

__attribute__((used)) static	Reclass*
newclass(void)
{
	if(nclass >= NCLASS)
		regerr2("too many character classes; limit", NCLASS+'0');
	return &(classp[nclass++]);
}