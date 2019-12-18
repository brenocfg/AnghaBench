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
struct phdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  profil (unsigned short*,scalar_t__,long,int /*<<< orphan*/ ) ; 
 int profiling ; 
 scalar_t__ s_lowpc ; 
 int /*<<< orphan*/  s_scale ; 
 scalar_t__ sbuf ; 
 scalar_t__ ssiz ; 

__attribute__((used)) static void moncontrol(int mode)
{
    if (mode) {
	/* start */
	profil((unsigned short *)(sbuf + sizeof(struct phdr)),
	       ssiz - sizeof(struct phdr),
	       (long)s_lowpc, s_scale);
	profiling = 0;
    } else {
	/* stop */
	profil((unsigned short *)0, 0, 0, 0);
	profiling = 3;
    }
}