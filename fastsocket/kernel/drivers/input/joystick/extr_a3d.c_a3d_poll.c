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
struct gameport {int dummy; } ;
struct a3d {scalar_t__ length; unsigned char mode; int /*<<< orphan*/  bads; int /*<<< orphan*/  gameport; int /*<<< orphan*/  reads; } ;

/* Variables and functions */
 int A3D_MAX_LENGTH ; 
 scalar_t__ a3d_csum (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  a3d_read (struct a3d*,unsigned char*) ; 
 scalar_t__ a3d_read_packet (int /*<<< orphan*/ ,scalar_t__,unsigned char*) ; 
 struct a3d* gameport_get_drvdata (struct gameport*) ; 

__attribute__((used)) static void a3d_poll(struct gameport *gameport)
{
	struct a3d *a3d = gameport_get_drvdata(gameport);
	unsigned char data[A3D_MAX_LENGTH];

	a3d->reads++;
	if (a3d_read_packet(a3d->gameport, a3d->length, data) != a3d->length ||
	    data[0] != a3d->mode || a3d_csum(data, a3d->length))
		a3d->bads++;
	else
		a3d_read(a3d, data);
}