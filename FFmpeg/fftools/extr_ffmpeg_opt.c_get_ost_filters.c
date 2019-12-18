#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* codecpar; int /*<<< orphan*/  index; } ;
struct TYPE_6__ {char* filters; scalar_t__ filters_script; TYPE_3__* st; } ;
struct TYPE_5__ {scalar_t__ codec_type; } ;
typedef  TYPE_2__ OutputStream ;
typedef  int /*<<< orphan*/  OptionsContext ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* av_strdup (char*) ; 
 int /*<<< orphan*/  exit_program (int) ; 
 int /*<<< orphan*/  nb_output_files ; 
 char* read_file (scalar_t__) ; 

__attribute__((used)) static char *get_ost_filters(OptionsContext *o, AVFormatContext *oc,
                             OutputStream *ost)
{
    AVStream *st = ost->st;

    if (ost->filters_script && ost->filters) {
        av_log(NULL, AV_LOG_ERROR, "Both -filter and -filter_script set for "
               "output stream #%d:%d.\n", nb_output_files, st->index);
        exit_program(1);
    }

    if (ost->filters_script)
        return read_file(ost->filters_script);
    else if (ost->filters)
        return av_strdup(ost->filters);

    return av_strdup(st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO ?
                     "null" : "anull");
}