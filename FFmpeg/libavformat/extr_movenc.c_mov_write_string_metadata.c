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
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_1__ AVDictionaryEntry ;

/* Variables and functions */
 TYPE_1__* get_metadata_lang (int /*<<< orphan*/ *,char const*,int*) ; 
 int mov_write_string_tag (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mov_write_string_metadata(AVFormatContext *s, AVIOContext *pb,
                                     const char *name, const char *tag,
                                     int long_style)
{
    int lang;
    AVDictionaryEntry *t = get_metadata_lang(s, tag, &lang);
    if (!t)
        return 0;
    return mov_write_string_tag(pb, name, t->value, lang, long_style);
}