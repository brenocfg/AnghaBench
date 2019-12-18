#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct section {int /*<<< orphan*/  unique_name; int /*<<< orphan*/  entries_to_show; scalar_t__ show_all_entries; } ;
struct TYPE_9__ {size_t level; int /*<<< orphan*/ * nb_item; TYPE_1__* writer; struct section** section; } ;
typedef  TYPE_2__ WriterContext ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  (* print_string ) (TYPE_2__*,char const*,char const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int PRINT_STRING_OPT ; 
 int PRINT_STRING_VALIDATE ; 
 int WRITER_FLAG_DISPLAY_OPTIONAL_FIELDS ; 
 scalar_t__ av_dict_get (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,char const*,char const*) ; 
 int validate_string (TYPE_2__*,char**,char const*) ; 

__attribute__((used)) static inline int writer_print_string(WriterContext *wctx,
                                      const char *key, const char *val, int flags)
{
    const struct section *section = wctx->section[wctx->level];
    int ret = 0;

    if ((flags & PRINT_STRING_OPT)
        && !(wctx->writer->flags & WRITER_FLAG_DISPLAY_OPTIONAL_FIELDS))
        return 0;

    if (section->show_all_entries || av_dict_get(section->entries_to_show, key, NULL, 0)) {
        if (flags & PRINT_STRING_VALIDATE) {
            char *key1 = NULL, *val1 = NULL;
            ret = validate_string(wctx, &key1, key);
            if (ret < 0) goto end;
            ret = validate_string(wctx, &val1, val);
            if (ret < 0) goto end;
            wctx->writer->print_string(wctx, key1, val1);
        end:
            if (ret < 0) {
                av_log(wctx, AV_LOG_ERROR,
                       "Invalid key=value string combination %s=%s in section %s\n",
                       key, val, section->unique_name);
            }
            av_free(key1);
            av_free(val1);
        } else {
            wctx->writer->print_string(wctx, key, val);
        }

        wctx->nb_item[wctx->level]++;
    }

    return ret;
}