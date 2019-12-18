#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* name; } ;
struct TYPE_6__ {struct TYPE_6__* zip; scalar_t__ fp; struct TYPE_6__* ecd; struct TYPE_6__* cd; TYPE_1__ ent; } ;
typedef  TYPE_2__ ZIP ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void closezip(ZIP* zip) {
	/* release all */
	free(zip->ent.name);
	free(zip->cd);
	free(zip->ecd);
	/* only if not suspended */
	if (zip->fp)
		fclose(zip->fp);
	free(zip->zip);
	free(zip);
}