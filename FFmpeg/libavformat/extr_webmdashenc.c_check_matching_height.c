#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__** streams; } ;
struct TYPE_9__ {int nb_streams; size_t* streams; } ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {int height; } ;
typedef  TYPE_3__ AdaptationSet ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */

__attribute__((used)) static int check_matching_height(AVFormatContext *s, AdaptationSet *as) {
    int first_height, i;
    if (as->nb_streams < 2) return 1;
    first_height = s->streams[as->streams[0]]->codecpar->height;
    for (i = 1; i < as->nb_streams; i++)
        if (first_height != s->streams[as->streams[i]]->codecpar->height)
          return 0;
    return 1;
}