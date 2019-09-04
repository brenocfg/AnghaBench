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
struct TYPE_3__ {size_t size_; int /*<<< orphan*/  data_; } ;
typedef  TYPE_1__ FuzzDataBuffer ;

/* Variables and functions */
 size_t AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_malloc (size_t) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void FDBRealloc(FuzzDataBuffer *FDB, size_t size) {
    size_t needed = size + AV_INPUT_BUFFER_PADDING_SIZE;
    av_assert0(needed > size);
    if (needed > FDB->size_) {
        av_free(FDB->data_);
        FDB->size_ = needed;
        FDB->data_ = av_malloc(FDB->size_);
        if (!FDB->data_)
            error("Failed memory allocation");
    }
}