#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gspca_dev {int nframes; int /*<<< orphan*/  memory; int /*<<< orphan*/ * capt_file; scalar_t__ frsz; TYPE_1__* frame; int /*<<< orphan*/ * frbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int /*<<< orphan*/  GSPCA_MEMORY_NO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void frame_free(struct gspca_dev *gspca_dev)
{
	int i;

	PDEBUG(D_STREAM, "frame free");
	if (gspca_dev->frbuf != NULL) {
		vfree(gspca_dev->frbuf);
		gspca_dev->frbuf = NULL;
		for (i = 0; i < gspca_dev->nframes; i++)
			gspca_dev->frame[i].data = NULL;
	}
	gspca_dev->nframes = 0;
	gspca_dev->frsz = 0;
	gspca_dev->capt_file = NULL;
	gspca_dev->memory = GSPCA_MEMORY_NO;
}