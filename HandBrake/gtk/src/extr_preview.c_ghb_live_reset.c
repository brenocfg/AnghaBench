#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* preview; } ;
typedef  TYPE_2__ signal_user_data_t ;
typedef  scalar_t__ gboolean ;
struct TYPE_6__ {int live_id; int encode_frame; size_t frame; scalar_t__* encoded; int /*<<< orphan*/ * current; int /*<<< orphan*/  pause; } ;

/* Variables and functions */
 int GHB_PREVIEW_MAX ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_set_preview_image (TYPE_2__*) ; 
 int /*<<< orphan*/  ghb_stop_live_encode () ; 
 int /*<<< orphan*/  live_preview_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 

void
ghb_live_reset(signal_user_data_t *ud)
{
    gboolean encoded;

    if (ud->preview->live_id >= 0)
    {
        ghb_stop_live_encode();
    }
    ud->preview->live_id = -1;
    ud->preview->encode_frame = -1;
    if (!ud->preview->pause)
        live_preview_stop(ud);
    if (ud->preview->current)
    {
        g_free(ud->preview->current);
        ud->preview->current = NULL;
    }
    encoded = ud->preview->encoded[ud->preview->frame];
    memset(ud->preview->encoded, 0, sizeof(gboolean) * GHB_PREVIEW_MAX);
    if (encoded)
        ghb_set_preview_image(ud);
}