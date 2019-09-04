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
struct TYPE_4__ {int /*<<< orphan*/  value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  AV_DICT_IGNORE_SUFFIX ; 
 TYPE_1__* av_dict_get (int /*<<< orphan*/ *,char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  write_escape_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_tags(AVIOContext *s, AVDictionary *m)
{
    AVDictionaryEntry *t = NULL;
    while ((t = av_dict_get(m, "", t, AV_DICT_IGNORE_SUFFIX))) {
        write_escape_str(s, t->key);
        avio_w8(s, '=');
        write_escape_str(s, t->value);
        avio_w8(s, '\n');
    }
}