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
struct TYPE_3__ {int /*<<< orphan*/ ** data; } ;
typedef  TYPE_1__ ThreadData ;

/* Variables and functions */
 int NUM_PLANES ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cleanup_derivative_buffers(ThreadData *td, int nb_buff, int nb_planes)
{
    int b, p;

    for (b = 0; b < nb_buff; ++b) {
        for (p = 0; p < NUM_PLANES; ++p) {
            av_freep(&td->data[b][p]);
        }
    }
    // Final buffer may not be fully allocated at fail cases
    for (p = 0; p < nb_planes; ++p) {
        av_freep(&td->data[b][p]);
    }
}