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
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  HDCS_STATE_RUN ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int hdcs_set_state (struct sd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hdcs_start(struct sd *sd)
{
	PDEBUG(D_STREAM, "Starting stream");

	return hdcs_set_state(sd, HDCS_STATE_RUN);
}