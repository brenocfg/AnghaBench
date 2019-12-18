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
struct gstr {int len; int /*<<< orphan*/  s; scalar_t__ max_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

struct gstr str_new(void)
{
	struct gstr gs;
	gs.s = malloc(sizeof(char) * 64);
	gs.len = 64;
	gs.max_width = 0;
	strcpy(gs.s, "\0");
	return gs;
}