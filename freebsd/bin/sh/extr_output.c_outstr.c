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
struct output {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  outbin (char const*,int /*<<< orphan*/ ,struct output*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void
outstr(const char *p, struct output *file)
{
	outbin(p, strlen(p), file);
}