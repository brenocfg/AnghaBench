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
typedef  char uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  metadata; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int ID3v1_GENRE_MAX ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_dict_set_int (int /*<<< orphan*/ *,char*,char const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_id3v1_genre_str ; 
 int /*<<< orphan*/  get_string (TYPE_1__*,char*,char const*,int) ; 

__attribute__((used)) static int parse_tag(AVFormatContext *s, const uint8_t *buf)
{
    int genre;

    if (!(buf[0] == 'T' &&
          buf[1] == 'A' &&
          buf[2] == 'G'))
        return -1;
    get_string(s, "title",   buf +  3, 30);
    get_string(s, "artist",  buf + 33, 30);
    get_string(s, "album",   buf + 63, 30);
    get_string(s, "date",    buf + 93,  4);
    get_string(s, "comment", buf + 97, 30);
    if (buf[125] == 0 && buf[126] != 0) {
        av_dict_set_int(&s->metadata, "track", buf[126], 0);
    }
    genre = buf[127];
    if (genre <= ID3v1_GENRE_MAX)
        av_dict_set(&s->metadata, "genre", ff_id3v1_genre_str[genre], 0);
    return 0;
}