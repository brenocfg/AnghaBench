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
 int /*<<< orphan*/  GLINTCACHECREATE_ID ; 
 int /*<<< orphan*/  RPC_CALL1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_UINT (int) ; 
 int /*<<< orphan*/  glintCacheCreate_impl ; 

__attribute__((used)) static void send_create(CLIENT_THREAD_STATE_T *thread, int base)
{
   RPC_CALL1(glintCacheCreate_impl,
             thread,
             GLINTCACHECREATE_ID,
             RPC_UINT(base));
}