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
typedef  int /*<<< orphan*/  date ;
struct TYPE_3__ {char* value; } ;
typedef  TYPE_1__ AVDictionaryEntry ;
typedef  int /*<<< orphan*/  AVDictionary ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 TYPE_1__* get_date_tag (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 

__attribute__((used)) static void merge_date(AVDictionary **m)
{
    AVDictionaryEntry *t;
    char date[17] = { 0 };      // YYYY-MM-DD hh:mm

    if (!(t = get_date_tag(*m, "TYER")) &&
        !(t = get_date_tag(*m, "TYE")))
        return;
    av_strlcpy(date, t->value, 5);
    av_dict_set(m, "TYER", NULL, 0);
    av_dict_set(m, "TYE", NULL, 0);

    if (!(t = get_date_tag(*m, "TDAT")) &&
        !(t = get_date_tag(*m, "TDA")))
        goto finish;
    snprintf(date + 4, sizeof(date) - 4, "-%.2s-%.2s", t->value + 2, t->value);
    av_dict_set(m, "TDAT", NULL, 0);
    av_dict_set(m, "TDA", NULL, 0);

    if (!(t = get_date_tag(*m, "TIME")) &&
        !(t = get_date_tag(*m, "TIM")))
        goto finish;
    snprintf(date + 10, sizeof(date) - 10,
             " %.2s:%.2s", t->value, t->value + 2);
    av_dict_set(m, "TIME", NULL, 0);
    av_dict_set(m, "TIM", NULL, 0);

finish:
    if (date[0])
        av_dict_set(m, "date", date, 0);
}