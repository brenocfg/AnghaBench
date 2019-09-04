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
typedef  char uint8_t ;
typedef  int /*<<< orphan*/  ebml_master ;
struct TYPE_3__ {char const* value; int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVDictionaryEntry ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LANG_ISO639_2_BIBL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  MATROSKA_ID_SIMPLETAG ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGLANG ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGNAME ; 
 int /*<<< orphan*/  MATROSKA_ID_TAGSTRING ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_ebml_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* ff_convert_lang_to (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_ebml_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  start_ebml_master (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static int mkv_write_simpletag(AVIOContext *pb, AVDictionaryEntry *t)
{
    uint8_t *key = av_strdup(t->key);
    uint8_t *p   = key;
    const uint8_t *lang = NULL;
    ebml_master tag;

    if (!key)
        return AVERROR(ENOMEM);

    if ((p = strrchr(p, '-')) &&
        (lang = ff_convert_lang_to(p + 1, AV_LANG_ISO639_2_BIBL)))
        *p = 0;

    p = key;
    while (*p) {
        if (*p == ' ')
            *p = '_';
        else if (*p >= 'a' && *p <= 'z')
            *p -= 'a' - 'A';
        p++;
    }

    tag = start_ebml_master(pb, MATROSKA_ID_SIMPLETAG, 0);
    put_ebml_string(pb, MATROSKA_ID_TAGNAME, key);
    if (lang)
        put_ebml_string(pb, MATROSKA_ID_TAGLANG, lang);
    put_ebml_string(pb, MATROSKA_ID_TAGSTRING, t->value);
    end_ebml_master(pb, tag);

    av_freep(&key);
    return 0;
}