#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data_ref; } ;
typedef  TYPE_1__ AV1RawTileData ;

/* Variables and functions */
 int /*<<< orphan*/  av_buffer_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cbs_av1_free_tile_data(AV1RawTileData *td)
{
    av_buffer_unref(&td->data_ref);
}