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
typedef  int /*<<< orphan*/  apr_bucket_brigade ;
typedef  int /*<<< orphan*/  apr_bucket ;

/* Variables and functions */
 int /*<<< orphan*/ * APR_BRIGADE_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * APR_BRIGADE_SENTINEL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * APR_BUCKET_NEXT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int count_buckets(apr_bucket_brigade *bb)
{
    apr_bucket *e;
    int count = 0;

    for (e = APR_BRIGADE_FIRST(bb); 
         e != APR_BRIGADE_SENTINEL(bb);
         e = APR_BUCKET_NEXT(e)) {
        count++;
    }
    
    return count;
}