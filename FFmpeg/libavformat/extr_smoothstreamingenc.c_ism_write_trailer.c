#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  filename ;
struct TYPE_7__ {char* url; TYPE_1__* priv_data; } ;
struct TYPE_6__ {scalar_t__ remove_at_exit; } ;
typedef  TYPE_1__ SmoothStreamingContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ism_flush (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ism_free (TYPE_2__*) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static int ism_write_trailer(AVFormatContext *s)
{
    SmoothStreamingContext *c = s->priv_data;
    ism_flush(s, 1);

    if (c->remove_at_exit) {
        char filename[1024];
        snprintf(filename, sizeof(filename), "%s/Manifest", s->url);
        unlink(filename);
        rmdir(s->url);
    }

    ism_free(s);
    return 0;
}