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
struct TYPE_6__ {int track_count; TYPE_1__* tracks; } ;
typedef  TYPE_2__ cue_data_t ;
struct TYPE_5__ {TYPE_2__* fname; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void cue_destroy(cue_data_t *data)
{
	int c;

	if (data == NULL) return;

	for (c = data->track_count; c > 0; c--)
		if (data->tracks[c].fname != NULL)
			free(data->tracks[c].fname);
	free(data);
}