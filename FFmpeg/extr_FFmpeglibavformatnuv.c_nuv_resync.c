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
typedef  int uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pb; } ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int MKBETAG (char,char,char,char) ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuv_resync(AVFormatContext *s, int64_t pos_limit) {
    AVIOContext *pb = s->pb;
    uint32_t tag = 0;
    while(!avio_feof(pb) && avio_tell(pb) < pos_limit) {
        tag = (tag << 8) | avio_r8(pb);
        if (tag                  == MKBETAG('R','T','j','j') &&
           (tag = avio_rb32(pb)) == MKBETAG('j','j','j','j') &&
           (tag = avio_rb32(pb)) == MKBETAG('j','j','j','j'))
            return 1;
    }
    return 0;
}