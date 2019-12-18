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
struct cardstate {unsigned int cmdbytes; } ;

/* Variables and functions */
 unsigned int IF_WRITEBUF ; 

__attribute__((used)) static int gigaset_write_room(struct cardstate *cs)
{
	unsigned bytes;

	bytes = cs->cmdbytes;
	return bytes < IF_WRITEBUF ? IF_WRITEBUF - bytes : 0;
}