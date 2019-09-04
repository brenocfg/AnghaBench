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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_3__ {int /*<<< orphan*/  metadata; int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_get_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 unsigned int avio_rb32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_info_chunk(AVFormatContext *s, int64_t size)
{
    AVIOContext *pb = s->pb;
    unsigned int i;
    unsigned int nb_entries = avio_rb32(pb);
    for (i = 0; i < nb_entries && !avio_feof(pb); i++) {
        char key[32];
        char value[1024];
        avio_get_str(pb, INT_MAX, key, sizeof(key));
        avio_get_str(pb, INT_MAX, value, sizeof(value));
        av_dict_set(&s->metadata, key, value, 0);
    }
}