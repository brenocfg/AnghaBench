#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* matches_contig_host; TYPE_1__* matches_host; } ;
struct TYPE_4__ {scalar_t__ should_consider; } ;
typedef  TYPE_1__ MotionVector ;
typedef  TYPE_2__ DeshakeOpenCLContext ;

/* Variables and functions */
 int MATCHES_CONTIG_SIZE ; 

__attribute__((used)) static int make_vectors_contig(
    DeshakeOpenCLContext *deshake_ctx,
    int size_y,
    int size_x
) {
    int num_vectors = 0;

    for (int i = 0; i < size_y; ++i) {
        for (int j = 0; j < size_x; ++j) {
            MotionVector v = deshake_ctx->matches_host[j + i * size_x];

            if (v.should_consider) {
                deshake_ctx->matches_contig_host[num_vectors] = v;
                ++num_vectors;
            }

            // Make sure we do not exceed the amount of space we allocated for these vectors
            if (num_vectors == MATCHES_CONTIG_SIZE - 1) {
                return num_vectors;
            }
        }
    }
    return num_vectors;
}