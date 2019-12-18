#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ttusb_dec {TYPE_4__* audio_filter; } ;
struct TYPE_8__ {TYPE_3__* feed; } ;
struct TYPE_6__ {int /*<<< orphan*/  ts; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ts ) (unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_2__ feed; TYPE_1__ cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMX_OK ; 
 int /*<<< orphan*/  stub1 (unsigned char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ttusb_dec_audio_pes2ts_cb(void *priv, unsigned char *data)
{
	struct ttusb_dec *dec = priv;

	dec->audio_filter->feed->cb.ts(data, 188, NULL, 0,
				       &dec->audio_filter->feed->feed.ts,
				       DMX_OK);

	return 0;
}