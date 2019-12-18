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
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  GLINTCACHEGROW_ID ; 
 int RPC_BOOLEAN_RES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_CALL0_RES (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glintCacheGrow_impl ; 

__attribute__((used)) static int send_grow(CLIENT_THREAD_STATE_T *thread)
{
   return RPC_BOOLEAN_RES(RPC_CALL0_RES(glintCacheGrow_impl,
                                        thread,
                                        GLINTCACHEGROW_ID));
}