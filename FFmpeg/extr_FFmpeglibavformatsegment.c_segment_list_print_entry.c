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
struct TYPE_3__ {char* filename; scalar_t__ start_time; scalar_t__ end_time; } ;
typedef  TYPE_1__ SegmentListEntry ;
typedef  int ListType ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_ESCAPE_FLAG_WHITESPACE ; 
 int /*<<< orphan*/  AV_ESCAPE_MODE_AUTO ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
#define  LIST_TYPE_CSV 132 
#define  LIST_TYPE_EXT 131 
#define  LIST_TYPE_FFCONCAT 130 
#define  LIST_TYPE_FLAT 129 
#define  LIST_TYPE_M3U8 128 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_escape (char**,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  avio_printf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  print_csv_escaped_str (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void segment_list_print_entry(AVIOContext      *list_ioctx,
                                     ListType          list_type,
                                     const SegmentListEntry *list_entry,
                                     void *log_ctx)
{
    switch (list_type) {
    case LIST_TYPE_FLAT:
        avio_printf(list_ioctx, "%s\n", list_entry->filename);
        break;
    case LIST_TYPE_CSV:
    case LIST_TYPE_EXT:
        print_csv_escaped_str(list_ioctx, list_entry->filename);
        avio_printf(list_ioctx, ",%f,%f\n", list_entry->start_time, list_entry->end_time);
        break;
    case LIST_TYPE_M3U8:
        avio_printf(list_ioctx, "#EXTINF:%f,\n%s\n",
                    list_entry->end_time - list_entry->start_time, list_entry->filename);
        break;
    case LIST_TYPE_FFCONCAT:
    {
        char *buf;
        if (av_escape(&buf, list_entry->filename, NULL, AV_ESCAPE_MODE_AUTO, AV_ESCAPE_FLAG_WHITESPACE) < 0) {
            av_log(log_ctx, AV_LOG_WARNING,
                   "Error writing list entry '%s' in list file\n", list_entry->filename);
            return;
        }
        avio_printf(list_ioctx, "file %s\n", buf);
        av_free(buf);
        break;
    }
    default:
        av_assert0(!"Invalid list type");
    }
}