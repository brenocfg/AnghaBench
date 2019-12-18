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
typedef  int /*<<< orphan*/  apr_bucket_file ;

/* Variables and functions */
 int /*<<< orphan*/  apr_bucket_free (int /*<<< orphan*/ *) ; 
 scalar_t__ apr_bucket_shared_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void file_bucket_destroy(void *data)
{
    apr_bucket_file *f = data;

    if (apr_bucket_shared_destroy(f)) {
        /* no need to close the file here; it will get
         * done automatically when the pool gets cleaned up */
        apr_bucket_free(f);
    }
}