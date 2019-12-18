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
struct zoltrix {int /*<<< orphan*/  curvol; scalar_t__ muted; } ;

/* Variables and functions */
 int /*<<< orphan*/  zol_setvol (struct zoltrix*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zol_unmute(struct zoltrix *zol)
{
	zol->muted = 0;
	zol_setvol(zol, zol->curvol);
}