#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_8__ {int /*<<< orphan*/  readorder; } ;
struct TYPE_7__ {int len; char* str; } ;
typedef  TYPE_1__ AVBPrint ;
typedef  TYPE_2__ ASSContext ;

/* Variables and functions */
 int atoi (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  av_bprint_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  av_bprintf (TYPE_1__*,char*,int /*<<< orphan*/ ,int const,int /*<<< orphan*/  const*) ; 
 int sscanf (int /*<<< orphan*/  const*,char*,int*,int*,int*,int*,int*,int*,int*,int*,int*) ; 

__attribute__((used)) static int read_dialogue(ASSContext *ass, AVBPrint *dst, const uint8_t *p,
                         int64_t *start, int *duration)
{
    int pos = 0;
    int64_t end;
    int hh1, mm1, ss1, ms1;
    int hh2, mm2, ss2, ms2;

    if (sscanf(p, "Dialogue: %*[^,],%d:%d:%d%*c%d,%d:%d:%d%*c%d,%n",
               &hh1, &mm1, &ss1, &ms1,
               &hh2, &mm2, &ss2, &ms2, &pos) >= 8 && pos > 0) {

        /* This is not part of the sscanf itself in order to handle an actual
         * number (which would be the Layer) or the form "Marked=N" (which is
         * the old SSA field, now replaced by Layer, and will lead to Layer
         * being 0 here). */
        const int layer = atoi(p + 10);

        end    = (hh2*3600LL + mm2*60LL + ss2) * 100LL + ms2;
        *start = (hh1*3600LL + mm1*60LL + ss1) * 100LL + ms1;
        *duration = end - *start;

        av_bprint_clear(dst);
        av_bprintf(dst, "%u,%d,%s", ass->readorder++, layer, p + pos);

        /* right strip the buffer */
        while (dst->len > 0 &&
               dst->str[dst->len - 1] == '\r' ||
               dst->str[dst->len - 1] == '\n')
            dst->str[--dst->len] = 0;
        return 0;
    }
    return -1;
}