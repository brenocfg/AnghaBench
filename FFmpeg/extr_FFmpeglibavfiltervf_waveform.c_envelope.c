#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int envelope; } ;
typedef  TYPE_1__ WaveformContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  envelope_instant (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  envelope_peak (TYPE_1__*,int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void envelope(WaveformContext *s, AVFrame *out, int plane, int component, int offset)
{
    if (s->envelope == 0) {
        return;
    } else if (s->envelope == 1) {
        envelope_instant(s, out, plane, component, offset);
    } else {
        envelope_peak(s, out, plane, component, offset);
    }
}