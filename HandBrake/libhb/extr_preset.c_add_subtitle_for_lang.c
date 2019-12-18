#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int* used; int one_burned; int burn_first; int /*<<< orphan*/  make_default; scalar_t__ burn_foreign; scalar_t__ burn_bd; scalar_t__ burn_dvd; scalar_t__ one; } ;
typedef  TYPE_2__ subtitle_behavior_t ;
typedef  int /*<<< orphan*/  hb_value_array_t ;
struct TYPE_11__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_3__ hb_title_t ;
struct TYPE_9__ {scalar_t__ default_track; } ;
struct TYPE_12__ {scalar_t__ source; int /*<<< orphan*/  name; TYPE_1__ config; } ;
typedef  TYPE_4__ hb_subtitle_t ;

/* Variables and functions */
 scalar_t__ PGSSUB ; 
 scalar_t__ VOBSUB ; 
 int /*<<< orphan*/  add_subtitle (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int find_subtitle_track (TYPE_3__*,char const*,int) ; 
 int /*<<< orphan*/  has_default_subtitle (int /*<<< orphan*/ *) ; 
 TYPE_4__* hb_list_item (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hb_subtitle_can_pass (scalar_t__,int) ; 

__attribute__((used)) static void add_subtitle_for_lang(hb_value_array_t *list, hb_title_t *title,
                                  int mux, const char *lang,
                                  subtitle_behavior_t *behavior)
{
    int t;
    for (t = find_subtitle_track(title, lang, 0);
         t >= 0;
         t = behavior->one ? -1 : find_subtitle_track(title, lang, t + 1))
    {
        if (behavior->used[t])
        {
            if (behavior->one)
                break;
            continue;
        }
        int burn, make_default;
        hb_subtitle_t *subtitle;
        subtitle = hb_list_item(title->list_subtitle, t);
        burn = !behavior->one_burned &&
               ((subtitle->source == VOBSUB && behavior->burn_dvd) ||
                (subtitle->source == PGSSUB && behavior->burn_bd)  ||
                !hb_subtitle_can_pass(subtitle->source, mux) ||
                behavior->burn_first || behavior->burn_foreign);
        // If the subtitle is added for foreign audio, or the source
        // subtitle was the default subtitle, mark this subtitle as
        // default.
        make_default = (!burn && behavior->make_default) ||
                       (!has_default_subtitle(list) &&
                        subtitle->config.default_track);
        behavior->burn_first &= !burn;
        behavior->one_burned |= burn;
        behavior->used[t] = 1;
        add_subtitle(list, t, make_default, 0 /*!force*/, burn, subtitle->name);
    }
}