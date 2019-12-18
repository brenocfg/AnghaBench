#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filename ;
struct TYPE_10__ {int /*<<< orphan*/  last_ts; } ;
struct TYPE_9__ {char* url; TYPE_1__* priv_data; } ;
struct TYPE_8__ {int nb_streams; scalar_t__ remove_at_exit; TYPE_7__* streams; } ;
typedef  TYPE_1__ HDSContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  hds_flush (TYPE_2__*,TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hds_free (TYPE_2__*) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  write_manifest (TYPE_2__*,int) ; 

__attribute__((used)) static int hds_write_trailer(AVFormatContext *s)
{
    HDSContext *c = s->priv_data;
    int i;

    for (i = 0; i < c->nb_streams; i++)
        hds_flush(s, &c->streams[i], 1, c->streams[i].last_ts);
    write_manifest(s, 1);

    if (c->remove_at_exit) {
        char filename[1024];
        snprintf(filename, sizeof(filename), "%s/index.f4m", s->url);
        unlink(filename);
        for (i = 0; i < c->nb_streams; i++) {
            snprintf(filename, sizeof(filename), "%s/stream%d.abst", s->url, i);
            unlink(filename);
        }
        rmdir(s->url);
    }

    hds_free(s);
    return 0;
}