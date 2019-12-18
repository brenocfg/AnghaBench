#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct maven_data {TYPE_3__* primary_head; } ;
struct TYPE_4__ {int brightness; int contrast; } ;
struct TYPE_5__ {TYPE_1__ tvo_params; } ;
struct TYPE_6__ {TYPE_2__ altout; } ;

/* Variables and functions */
 int BLMIN ; 
 int /*<<< orphan*/  WLMAX ; 
 int max (int const,int) ; 
 int min (int const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void maven_compute_bwlevel (const struct maven_data* md,
				   int *bl, int *wl) {
	const int b = md->primary_head->altout.tvo_params.brightness + BLMIN;
	const int c = md->primary_head->altout.tvo_params.contrast;

	*bl = max(b - c, BLMIN);
	*wl = min(b + c, WLMAX);
}