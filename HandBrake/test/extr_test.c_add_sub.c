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
typedef  int /*<<< orphan*/  hb_value_array_t ;
struct TYPE_5__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_1__ hb_title_t ;
struct TYPE_6__ {int /*<<< orphan*/  source; } ;
typedef  TYPE_2__ hb_subtitle_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 scalar_t__ hb_subtitle_can_burn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_subtitle_can_pass (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_bool (int) ; 
 int /*<<< orphan*/  hb_value_int (int) ; 
 int /*<<< orphan*/  mux ; 
 int /*<<< orphan*/  stderr ; 
 int subburn ; 
 int subdefault ; 
 int /*<<< orphan*/  subforce ; 
 int test_sub_list (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int add_sub(hb_value_array_t *list, hb_title_t *title, int track, int out_track, int *one_burned)
{
    hb_subtitle_t *subtitle;
    // Check that the track exists
    subtitle = hb_list_item(title->list_subtitle, track);
    if (subtitle == NULL)
    {
        fprintf(stderr, "Warning: Could not find subtitle track %d, skipped\n",
                track + 1);
        return -1;
    }

    int burn = !*one_burned && subburn == out_track &&
               hb_subtitle_can_burn(subtitle->source);
    *one_burned |= burn;
    int def  = subdefault == out_track;
    int force = test_sub_list(subforce, out_track);

    if (!burn &&
        !hb_subtitle_can_pass(subtitle->source, mux))
    {
        // Only allow one subtitle to be burned into video
        if (*one_burned)
        {
            fprintf(stderr, "Warning: Skipping subtitle track %d, can't have more than one track burnt in\n", track + 1);
            return -1;
        }
        *one_burned = 1;
    }
    hb_dict_t *subtitle_dict = hb_dict_init();
    hb_dict_set(subtitle_dict, "Track", hb_value_int(track));
    hb_dict_set(subtitle_dict, "Default", hb_value_bool(def));
    hb_dict_set(subtitle_dict, "Forced", hb_value_bool(force));
    hb_dict_set(subtitle_dict, "Burn", hb_value_bool(burn));
    hb_value_array_append(list, subtitle_dict);
    return 0;
}