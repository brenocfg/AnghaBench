#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  char uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVFormatContext ;
typedef  TYPE_2__ AVDictionaryEntry ;

/* Variables and functions */
 int ID3v1_GENRE_MAX ; 
 int /*<<< orphan*/  ID3v1_TAG_SIZE ; 
 char atoi (int /*<<< orphan*/ ) ; 
 TYPE_2__* av_dict_get (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_id3v1_genre_str ; 
 scalar_t__ id3v1_set_string (TYPE_1__*,char*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int id3v1_create_tag(AVFormatContext *s, uint8_t *buf)
{
    AVDictionaryEntry *tag;
    int i, count = 0;

    memset(buf, 0, ID3v1_TAG_SIZE); /* fail safe */
    buf[0] = 'T';
    buf[1] = 'A';
    buf[2] = 'G';
    /* we knowingly overspecify each tag length by one byte to compensate for the mandatory null byte added by av_strlcpy */
    count += id3v1_set_string(s, "TIT2",    buf +  3, 30 + 1);       //title
    count += id3v1_set_string(s, "TPE1",    buf + 33, 30 + 1);       //author|artist
    count += id3v1_set_string(s, "TALB",    buf + 63, 30 + 1);       //album
    count += id3v1_set_string(s, "TDRC",    buf + 93,  4 + 1);       //date
    count += id3v1_set_string(s, "comment", buf + 97, 30 + 1);
    if ((tag = av_dict_get(s->metadata, "TRCK", NULL, 0))) { //track
        buf[125] = 0;
        buf[126] = atoi(tag->value);
        count++;
    }
    buf[127] = 0xFF; /* default to unknown genre */
    if ((tag = av_dict_get(s->metadata, "TCON", NULL, 0))) { //genre
        for(i = 0; i <= ID3v1_GENRE_MAX; i++) {
            if (!av_strcasecmp(tag->value, ff_id3v1_genre_str[i])) {
                buf[127] = i;
                count++;
                break;
            }
        }
    }
    return count;
}