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
struct TYPE_3__ {scalar_t__ id; } ;
typedef  TYPE_1__ CodecMime ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_NONE ; 
 int MKTAG (char,char,char,char) ; 
 TYPE_1__* ff_id3v2_mime_tags ; 

__attribute__((used)) static int query_codec(enum AVCodecID id, int std_compliance)
{
    const CodecMime *cm= ff_id3v2_mime_tags;
    while(cm->id != AV_CODEC_ID_NONE) {
        if(id == cm->id)
            return MKTAG('A', 'P', 'I', 'C');
        cm++;
    }
    return -1;
}