#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* system; char* game; char* song; char* author; char* copyright; char* comment; char* dumper; } ;
typedef  TYPE_1__ gme_info_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_8__ {TYPE_2__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/  music_emu; TYPE_1__* info; } ;
typedef  TYPE_2__ GMEContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  add_meta (TYPE_3__*,char*,char*) ; 
 scalar_t__ gme_track_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int load_metadata(AVFormatContext *s)
{
    GMEContext *gme = s->priv_data;
    gme_info_t *info = gme->info;
    char buf[30];

    add_meta(s, "system",       info->system);
    add_meta(s, "game",         info->game);
    add_meta(s, "song",         info->song);
    add_meta(s, "author",       info->author);
    add_meta(s, "copyright",    info->copyright);
    add_meta(s, "comment",      info->comment);
    add_meta(s, "dumper",       info->dumper);

    snprintf(buf, sizeof(buf), "%d", (int)gme_track_count(gme->music_emu));
    add_meta(s, "tracks", buf);

    return 0;
}