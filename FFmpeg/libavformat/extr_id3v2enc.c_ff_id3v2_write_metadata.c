#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int nb_chapters; int /*<<< orphan*/  metadata; int /*<<< orphan*/  pb; } ;
struct TYPE_11__ {int version; } ;
typedef  TYPE_1__ ID3v2EncContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int ID3v2_ENCODING_UTF16BOM ; 
 int ID3v2_ENCODING_UTF8 ; 
 int /*<<< orphan*/  ff_standardize_creation_time (TYPE_2__*) ; 
 int write_chapter (TYPE_2__*,TYPE_1__*,int,int) ; 
 int write_ctoc (TYPE_2__*,TYPE_1__*,int) ; 
 int write_metadata (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int) ; 

int ff_id3v2_write_metadata(AVFormatContext *s, ID3v2EncContext *id3)
{
    int enc = id3->version == 3 ? ID3v2_ENCODING_UTF16BOM :
                                  ID3v2_ENCODING_UTF8;
    int i, ret;

    ff_standardize_creation_time(s);
    if ((ret = write_metadata(s->pb, &s->metadata, id3, enc)) < 0)
        return ret;

    if ((ret = write_ctoc(s, id3, enc)) < 0)
        return ret;

    for (i = 0; i < s->nb_chapters; i++) {
        if ((ret = write_chapter(s, id3, i, enc)) < 0)
            return ret;
    }

    return 0;
}