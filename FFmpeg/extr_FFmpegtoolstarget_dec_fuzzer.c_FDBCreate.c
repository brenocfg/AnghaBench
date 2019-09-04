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
struct TYPE_3__ {int size_; int /*<<< orphan*/  data_; } ;
typedef  TYPE_1__ FuzzDataBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  av_malloc (int) ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static void FDBCreate(FuzzDataBuffer *FDB) {
    FDB->size_ = 0x1000;
    FDB->data_ = av_malloc(FDB->size_);
    if (!FDB->data_)
        error("Failed memory allocation");
}