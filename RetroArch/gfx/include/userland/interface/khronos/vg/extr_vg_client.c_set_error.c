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
typedef  int /*<<< orphan*/  VGErrorCode ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/ * CLIENT_GET_THREAD_STATE () ; 
 int /*<<< orphan*/  RPC_CALL1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_ENUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGSETERROR_ID ; 
 int /*<<< orphan*/  vgSetError_impl ; 

__attribute__((used)) static void set_error(VGErrorCode error)
{
   CLIENT_THREAD_STATE_T *thread = CLIENT_GET_THREAD_STATE();
   RPC_CALL1(vgSetError_impl,
             thread,
             VGSETERROR_ID,
             RPC_ENUM(error));
}