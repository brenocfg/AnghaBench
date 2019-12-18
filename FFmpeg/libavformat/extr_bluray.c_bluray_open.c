#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_9__ {TYPE_2__* priv_data; } ;
typedef  TYPE_1__ URLContext ;
struct TYPE_11__ {int playlist; int duration; } ;
struct TYPE_10__ {int playlist; scalar_t__ angle; int chapter; int /*<<< orphan*/  bd; } ;
typedef  TYPE_2__ BlurayContext ;
typedef  TYPE_3__ BLURAY_TITLE_INFO ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  BLURAY_PROTO_PREFIX ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  MIN_PLAYLIST_LENGTH ; 
 int /*<<< orphan*/  TITLES_RELEVANT ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_strstart (char const*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  bd_free_title_info (TYPE_3__*) ; 
 TYPE_3__* bd_get_title_info (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int bd_get_titles (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bd_open (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bd_seek_chapter (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bd_select_angle (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ bd_select_playlist (int /*<<< orphan*/ ,int) ; 
 scalar_t__ check_disc_info (TYPE_1__*) ; 

__attribute__((used)) static int bluray_open(URLContext *h, const char *path, int flags)
{
    BlurayContext *bd = h->priv_data;
    int num_title_idx;
    const char *diskname = path;

    av_strstart(path, BLURAY_PROTO_PREFIX, &diskname);

    bd->bd = bd_open(diskname, NULL);
    if (!bd->bd) {
        av_log(h, AV_LOG_ERROR, "bd_open() failed\n");
        return AVERROR(EIO);
    }

    /* check if disc can be played */
    if (check_disc_info(h) < 0) {
        return AVERROR(EIO);
    }

    /* setup player registers */
    /* region code has no effect without menus
    if (bd->region > 0 && bd->region < 5) {
        av_log(h, AV_LOG_INFO, "setting region code to %d (%c)\n", bd->region, 'A' + (bd->region - 1));
        bd_set_player_setting(bd->bd, BLURAY_PLAYER_SETTING_REGION_CODE, bd->region);
    }
    */

    /* load title list */
    num_title_idx = bd_get_titles(bd->bd, TITLES_RELEVANT, MIN_PLAYLIST_LENGTH);
    av_log(h, AV_LOG_INFO, "%d usable playlists:\n", num_title_idx);
    if (num_title_idx < 1) {
        return AVERROR(EIO);
    }

    /* if playlist was not given, select longest playlist */
    if (bd->playlist < 0) {
        uint64_t duration = 0;
        int i;
        for (i = 0; i < num_title_idx; i++) {
            BLURAY_TITLE_INFO *info = bd_get_title_info(bd->bd, i, 0);

            av_log(h, AV_LOG_INFO, "playlist %05d.mpls (%d:%02d:%02d)\n",
                   info->playlist,
                   ((int)(info->duration / 90000) / 3600),
                   ((int)(info->duration / 90000) % 3600) / 60,
                   ((int)(info->duration / 90000) % 60));

            if (info->duration > duration) {
                bd->playlist = info->playlist;
                duration = info->duration;
            }

            bd_free_title_info(info);
        }
        av_log(h, AV_LOG_INFO, "selected %05d.mpls\n", bd->playlist);
    }

    /* select playlist */
    if (bd_select_playlist(bd->bd, bd->playlist) <= 0) {
        av_log(h, AV_LOG_ERROR, "bd_select_playlist(%05d.mpls) failed\n", bd->playlist);
        return AVERROR(EIO);
    }

    /* select angle */
    if (bd->angle >= 0) {
        bd_select_angle(bd->bd, bd->angle);
    }

    /* select chapter */
    if (bd->chapter > 1) {
        bd_seek_chapter(bd->bd, bd->chapter - 1);
    }

    return 0;
}