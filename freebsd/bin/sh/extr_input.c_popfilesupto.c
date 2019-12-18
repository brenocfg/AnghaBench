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
struct parsefile {int dummy; } ;

/* Variables and functions */
 struct parsefile basepf ; 
 int /*<<< orphan*/  error (char*) ; 
 struct parsefile* parsefile ; 
 int /*<<< orphan*/  popfile () ; 

void
popfilesupto(struct parsefile *file)
{
	while (parsefile != file && parsefile != &basepf)
		popfile();
	if (parsefile != file)
		error("popfilesupto() misused");
}