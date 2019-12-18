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
typedef  int /*<<< orphan*/  hb_list_t ;
struct TYPE_3__ {int /*<<< orphan*/  config; } ;
typedef  TYPE_1__ hb_audio_t ;
typedef  int /*<<< orphan*/  hb_audio_config_t ;

/* Variables and functions */
 TYPE_1__* hb_list_item (int /*<<< orphan*/ *,int) ; 

hb_audio_config_t * hb_list_audio_config_item(hb_list_t * list, int i)
{
    hb_audio_t *audio = NULL;

    if( (audio = hb_list_item(list, i)) )
        return &(audio->config);

    return NULL;
}