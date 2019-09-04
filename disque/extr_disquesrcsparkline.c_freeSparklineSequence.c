#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sequence {int length; struct sequence* samples; struct sequence* label; } ;

/* Variables and functions */
 int /*<<< orphan*/  zfree (struct sequence*) ; 

void freeSparklineSequence(struct sequence *seq) {
    int j;

    for (j = 0; j < seq->length; j++)
        zfree(seq->samples[j].label);
    zfree(seq->samples);
    zfree(seq);
}