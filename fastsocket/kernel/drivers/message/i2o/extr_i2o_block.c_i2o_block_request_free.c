#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2o_block_request {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 TYPE_1__ i2o_blk_req_pool ; 
 int /*<<< orphan*/  mempool_free (struct i2o_block_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i2o_block_request_free(struct i2o_block_request *ireq)
{
	mempool_free(ireq, i2o_blk_req_pool.pool);
}