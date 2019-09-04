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
struct AVAESCTR {int /*<<< orphan*/  aes; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_free (struct AVAESCTR*) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

void av_aes_ctr_free(struct AVAESCTR *a)
{
    if (a) {
        av_freep(&a->aes);
        av_free(a);
    }
}