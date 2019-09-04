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
typedef  TYPE_1__ VectorscopeContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  envelope_instant (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  envelope_peak (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void envelope(VectorscopeContext *s, AVFrame *out)
{
    if (!s->envelope) {
        return;
    } else if (s->envelope == 1) {
        envelope_instant(s, out);
    } else {
        envelope_peak(s, out);
    }
}