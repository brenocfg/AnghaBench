#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct section {int show_all_entries; size_t* children_ids; int /*<<< orphan*/  entries_to_show; } ;
typedef  size_t SectionID ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct section* sections ; 

__attribute__((used)) static inline void mark_section_show_entries(SectionID section_id,
                                             int show_all_entries, AVDictionary *entries)
{
    struct section *section = &sections[section_id];

    section->show_all_entries = show_all_entries;
    if (show_all_entries) {
        SectionID *id;
        for (id = section->children_ids; *id != -1; id++)
            mark_section_show_entries(*id, show_all_entries, entries);
    } else {
        av_dict_copy(&section->entries_to_show, entries, 0);
    }
}