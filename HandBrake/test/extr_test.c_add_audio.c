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
typedef  int /*<<< orphan*/  hb_value_array_t ;
struct TYPE_3__ {int /*<<< orphan*/  list_audio; } ;
typedef  TYPE_1__ hb_title_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int add_audio(hb_value_array_t *list, hb_title_t *title, int track)
{
    // Check that the track exists
    if (hb_list_item(title->list_audio, track-1) == NULL)
    {
        fprintf(stderr, "Warning: Could not find audio track %d, skipped\n",
                track);
        return -1;
    }
    hb_dict_t *audio_dict = hb_dict_init();
    hb_dict_set(audio_dict, "Track", hb_value_int(track-1));
    hb_value_array_append(list, audio_dict);

    return 0;
}