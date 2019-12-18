#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_3__ hb_title_t ;
typedef  int /*<<< orphan*/  hb_handle_t ;
struct TYPE_7__ {int /*<<< orphan*/  codec_param; int /*<<< orphan*/  codec; } ;
struct TYPE_8__ {TYPE_1__ in; } ;
struct TYPE_10__ {TYPE_2__ config; } ;
typedef  TYPE_4__ hb_audio_t ;

/* Variables and functions */
 int hb_audio_can_apply_drc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* hb_find_title_by_index (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int) ; 

int hb_audio_can_apply_drc2(hb_handle_t *h, int title_idx, int audio_idx, int encoder)
{
    hb_title_t *title = hb_find_title_by_index(h, title_idx);
    if (title == NULL)
        return 0;

    hb_audio_t *audio = hb_list_item(title->list_audio, audio_idx);
    if (audio == NULL)
        return 0;

    return hb_audio_can_apply_drc(audio->config.in.codec,
                                  audio->config.in.codec_param, encoder);
}