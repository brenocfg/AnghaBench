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
struct TYPE_3__ {int alignment_applied; } ;
typedef  TYPE_1__ SRTContext ;

/* Variables and functions */
 int /*<<< orphan*/  srt_print (TYPE_1__*,char*,int) ; 

__attribute__((used)) static void srt_alignment_cb(void *priv, int alignment)
{
    SRTContext *s = priv;
    if (!s->alignment_applied && alignment >= 0) {
        srt_print(s, "{\\an%d}", alignment);
        s->alignment_applied = 1;
    }
}