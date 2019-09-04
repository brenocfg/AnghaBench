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
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {int /*<<< orphan*/  buf_size; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  FFTextReader ;
typedef  TYPE_1__ AVProbeData ;

/* Variables and functions */
 int AVPROBE_SCORE_EXTENSION ; 
 int /*<<< orphan*/  av_strncasecmp (char*,char*,int) ; 
 int /*<<< orphan*/  ff_text_init_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_text_read (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int realtext_probe(const AVProbeData *p)
{
    char buf[7];
    FFTextReader tr;
    ff_text_init_buf(&tr, p->buf, p->buf_size);
    ff_text_read(&tr, buf, sizeof(buf));

    return !av_strncasecmp(buf, "<window", 7) ? AVPROBE_SCORE_EXTENSION : 0;
}