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
typedef  int /*<<< orphan*/  filename ;
struct TYPE_11__ {TYPE_2__* priv_data; } ;
struct TYPE_10__ {char* dirname; int /*<<< orphan*/  single_file; } ;
struct TYPE_9__ {int pos; int init_range_length; int /*<<< orphan*/  out; int /*<<< orphan*/  initfile; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ DASHContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  dashenc_io_close (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int flush_dynbuf (TYPE_2__*,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flush_init_segment(AVFormatContext *s, OutputStream *os)
{
    DASHContext *c = s->priv_data;
    int ret, range_length;

    ret = flush_dynbuf(c, os, &range_length);
    if (ret < 0)
        return ret;

    os->pos = os->init_range_length = range_length;
    if (!c->single_file) {
        char filename[1024];
        snprintf(filename, sizeof(filename), "%s%s", c->dirname, os->initfile);
        dashenc_io_close(s, &os->out, filename);
    }
    return 0;
}