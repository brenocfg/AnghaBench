#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct variant_info {int /*<<< orphan*/  subtitles; int /*<<< orphan*/  video; int /*<<< orphan*/  audio; int /*<<< orphan*/  bandwidth; } ;
struct variant {int /*<<< orphan*/  n_playlists; int /*<<< orphan*/  playlists; int /*<<< orphan*/  subtitles_group; int /*<<< orphan*/  video_group; int /*<<< orphan*/  audio_group; int /*<<< orphan*/  bandwidth; } ;
struct playlist {int /*<<< orphan*/  n_playlists; int /*<<< orphan*/  playlists; int /*<<< orphan*/  subtitles_group; int /*<<< orphan*/  video_group; int /*<<< orphan*/  audio_group; int /*<<< orphan*/  bandwidth; } ;
struct TYPE_4__ {int /*<<< orphan*/  n_variants; int /*<<< orphan*/  variants; } ;
typedef  TYPE_1__ HLSContext ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (int /*<<< orphan*/ ) ; 
 struct variant* av_mallocz (int) ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct variant*) ; 
 struct variant* new_playlist (TYPE_1__*,char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct variant *new_variant(HLSContext *c, struct variant_info *info,
                                   const char *url, const char *base)
{
    struct variant *var;
    struct playlist *pls;

    pls = new_playlist(c, url, base);
    if (!pls)
        return NULL;

    var = av_mallocz(sizeof(struct variant));
    if (!var)
        return NULL;

    if (info) {
        var->bandwidth = atoi(info->bandwidth);
        strcpy(var->audio_group, info->audio);
        strcpy(var->video_group, info->video);
        strcpy(var->subtitles_group, info->subtitles);
    }

    dynarray_add(&c->variants, &c->n_variants, var);
    dynarray_add(&var->playlists, &var->n_playlists, pls);
    return var;
}