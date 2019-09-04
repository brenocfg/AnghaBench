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
typedef  enum AVMediaType { ____Placeholder_AVMediaType } AVMediaType ;
struct TYPE_3__ {int /*<<< orphan*/  index; int /*<<< orphan*/  file_index; scalar_t__ filters_script; scalar_t__ filters; } ;
typedef  TYPE_1__ OutputStream ;
typedef  int /*<<< orphan*/  OptionsContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_get_media_type_string (int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_program (int) ; 

__attribute__((used)) static void check_streamcopy_filters(OptionsContext *o, AVFormatContext *oc,
                                     const OutputStream *ost, enum AVMediaType type)
{
    if (ost->filters_script || ost->filters) {
        av_log(NULL, AV_LOG_ERROR,
               "%s '%s' was defined for %s output stream %d:%d but codec copy was selected.\n"
               "Filtering and streamcopy cannot be used together.\n",
               ost->filters ? "Filtergraph" : "Filtergraph script",
               ost->filters ? ost->filters : ost->filters_script,
               av_get_media_type_string(type), ost->file_index, ost->index);
        exit_program(1);
    }
}