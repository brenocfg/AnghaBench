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

/* Variables and functions */
 int /*<<< orphan*/  BIO_AOF_FSYNC ; 
 int /*<<< orphan*/  bioCreateBackgroundJob (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void aof_background_fsync(int fd) {
    bioCreateBackgroundJob(BIO_AOF_FSYNC,(void*)(long)fd,NULL,NULL);
}