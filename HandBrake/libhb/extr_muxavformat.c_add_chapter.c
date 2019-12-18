#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  time_base; TYPE_1__* oc; } ;
typedef  TYPE_2__ hb_mux_object_t ;
struct TYPE_10__ {int id; int /*<<< orphan*/  metadata; void* end; void* start; int /*<<< orphan*/  time_base; } ;
struct TYPE_8__ {int nb_chapters; TYPE_3__** chapters; } ;
typedef  TYPE_3__ AVChapter ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* av_mallocz (int) ; 
 TYPE_3__** av_realloc (TYPE_3__**,int) ; 
 int /*<<< orphan*/  hb_error (char*) ; 

__attribute__((used)) static int add_chapter(hb_mux_object_t *m, int64_t start, int64_t end, char * title)
{
    AVChapter *chap;
    AVChapter **chapters;
    int nchap = m->oc->nb_chapters;

    nchap++;
    chapters = av_realloc(m->oc->chapters, nchap * sizeof(AVChapter*));
    if (chapters == NULL)
    {
        hb_error("chapter array: malloc failure");
        return -1;
    }

    chap = av_mallocz(sizeof(AVChapter));
    if (chap == NULL)
    {
        hb_error("chapter: malloc failure");
        return -1;
    }

    m->oc->chapters = chapters;
    m->oc->chapters[nchap-1] = chap;
    m->oc->nb_chapters = nchap;

    chap->id = nchap;
    chap->time_base = m->time_base;
    // libav does not currently have a good way to deal with chapters and
    // delayed stream timestamps.  It makes no corrections to the chapter
    // track.  A patch to libav would touch a lot of things, so for now,
    // work around the issue here.
    chap->start = start;
    chap->end = end;
    av_dict_set(&chap->metadata, "title", title, 0);

    return 0;
}