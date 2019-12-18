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
struct variant {TYPE_2__** playlists; int /*<<< orphan*/  n_playlists; } ;
struct rendition {int type; struct rendition* playlist; int /*<<< orphan*/  group_id; } ;
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_5__ {int /*<<< orphan*/  n_renditions; struct TYPE_5__** renditions; } ;
struct TYPE_4__ {int n_renditions; struct rendition** renditions; } ;
typedef  TYPE_1__ HLSContext ;

/* Variables and functions */
 int /*<<< orphan*/  dynarray_add (TYPE_2__***,int /*<<< orphan*/ *,struct rendition*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void add_renditions_to_variant(HLSContext *c, struct variant *var,
                                      enum AVMediaType type, const char *group_id)
{
    int i;

    for (i = 0; i < c->n_renditions; i++) {
        struct rendition *rend = c->renditions[i];

        if (rend->type == type && !strcmp(rend->group_id, group_id)) {

            if (rend->playlist)
                /* rendition is an external playlist
                 * => add the playlist to the variant */
                dynarray_add(&var->playlists, &var->n_playlists, rend->playlist);
            else
                /* rendition is part of the variant main Media Playlist
                 * => add the rendition to the main Media Playlist */
                dynarray_add(&var->playlists[0]->renditions,
                             &var->playlists[0]->n_renditions,
                             rend);
        }
    }
}