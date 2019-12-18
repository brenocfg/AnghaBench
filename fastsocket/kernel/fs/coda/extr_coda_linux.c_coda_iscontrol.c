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
 int /*<<< orphan*/  CODA_CONTROL ; 
 size_t CODA_CONTROLLEN ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,size_t) ; 

int coda_iscontrol(const char *name, size_t length)
{
	return ((CODA_CONTROLLEN == length) && 
                (strncmp(name, CODA_CONTROL, CODA_CONTROLLEN) == 0));
}