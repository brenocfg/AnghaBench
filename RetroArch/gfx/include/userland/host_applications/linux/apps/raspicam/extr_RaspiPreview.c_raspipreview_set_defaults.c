#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int width; int height; scalar_t__ y; scalar_t__ x; } ;
struct TYPE_5__ {int wantPreview; int wantFullScreenPreview; int opacity; int /*<<< orphan*/ * preview_component; TYPE_1__ previewWindow; } ;
typedef  TYPE_2__ RASPIPREVIEW_PARAMETERS ;

/* Variables and functions */

void raspipreview_set_defaults(RASPIPREVIEW_PARAMETERS *state)
{
   state->wantPreview = 1;
   state->wantFullScreenPreview = 1;
   state->opacity = 255;
   state->previewWindow.x = 0;
   state->previewWindow.y = 0;
   state->previewWindow.width = 1024;
   state->previewWindow.height = 768;
   state->preview_component = NULL;
}