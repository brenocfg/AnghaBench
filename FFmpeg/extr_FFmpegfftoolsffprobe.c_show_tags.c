#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WriterContext ;
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int print_str_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writer_print_section_footer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writer_print_section_header (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline int show_tags(WriterContext *w, AVDictionary *tags, int section_id)
{
    AVDictionaryEntry *tag = NULL;
    int ret = 0;

    if (!tags)
        return 0;
    writer_print_section_header(w, section_id);

    while ((tag = av_dict_get(tags, "", tag, AV_DICT_IGNORE_SUFFIX))) {
        if ((ret = print_str_validate(tag->key, tag->value)) < 0)
            break;
    }
    writer_print_section_footer(w);

    return ret;
}