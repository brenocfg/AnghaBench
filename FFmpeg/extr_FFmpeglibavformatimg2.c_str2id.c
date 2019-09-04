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
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_3__ {int id; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ IdStrMap ;

/* Variables and functions */
 int AV_CODEC_ID_NONE ; 
 int /*<<< orphan*/  av_strcasecmp (char const*,int /*<<< orphan*/ ) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static enum AVCodecID str2id(const IdStrMap *tags, const char *str)
{
    str = strrchr(str, '.');
    if (!str)
        return AV_CODEC_ID_NONE;
    str++;

    while (tags->id) {
        if (!av_strcasecmp(str, tags->str))
            return tags->id;

        tags++;
    }
    return AV_CODEC_ID_NONE;
}