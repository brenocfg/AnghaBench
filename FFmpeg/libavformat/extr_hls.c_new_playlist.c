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
struct playlist {int is_id3_timestamped; void* id3_mpegts_timestamp; void* seek_timestamp; int /*<<< orphan*/  url; int /*<<< orphan*/  pkt; } ;
struct TYPE_3__ {int /*<<< orphan*/  n_playlists; int /*<<< orphan*/  playlists; } ;
typedef  TYPE_1__ HLSContext ;

/* Variables and functions */
 void* AV_NOPTS_VALUE ; 
 struct playlist* av_mallocz (int) ; 
 int /*<<< orphan*/  dynarray_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct playlist*) ; 
 int /*<<< orphan*/  ff_make_absolute_url (int /*<<< orphan*/ ,int,char const*,char const*) ; 
 int /*<<< orphan*/  reset_packet (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct playlist *new_playlist(HLSContext *c, const char *url,
                                     const char *base)
{
    struct playlist *pls = av_mallocz(sizeof(struct playlist));
    if (!pls)
        return NULL;
    reset_packet(&pls->pkt);
    ff_make_absolute_url(pls->url, sizeof(pls->url), base, url);
    pls->seek_timestamp = AV_NOPTS_VALUE;

    pls->is_id3_timestamped = -1;
    pls->id3_mpegts_timestamp = AV_NOPTS_VALUE;

    dynarray_add(&c->playlists, &c->n_playlists, pls);
    return pls;
}