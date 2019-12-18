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
struct nubus_dirent {unsigned char* base; int /*<<< orphan*/  mask; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  nubus_expand32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nubus_move (unsigned char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char *nubus_dirptr(const struct nubus_dirent *nd)
{
	unsigned char *p = nd->base;
	/* Essentially, just step over the bytelanes using whatever
	   offset we might have found */
	nubus_move(&p, nubus_expand32(nd->data), nd->mask);
	/* And return the value */
	return p;
}