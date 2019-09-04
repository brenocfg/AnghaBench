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
struct representation {int dummy; } ;
struct TYPE_3__ {int n_videos; struct representation** videos; } ;
typedef  TYPE_1__ DASHContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (struct representation***) ; 
 int /*<<< orphan*/  free_representation (struct representation*) ; 

__attribute__((used)) static void free_video_list(DASHContext *c)
{
    int i;
    for (i = 0; i < c->n_videos; i++) {
        struct representation *pls = c->videos[i];
        free_representation(pls);
    }
    av_freep(&c->videos);
    c->n_videos = 0;
}