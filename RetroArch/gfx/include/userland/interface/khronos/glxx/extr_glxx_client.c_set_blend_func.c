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
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  CLIENT_THREAD_STATE_T ;

/* Variables and functions */
 int /*<<< orphan*/  GLBLENDFUNCSEPARATE_ID ; 
 int /*<<< orphan*/  RPC_CALL4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPC_ENUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBlendFuncSeparate_impl ; 

__attribute__((used)) static void set_blend_func (CLIENT_THREAD_STATE_T *thread, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {
   RPC_CALL4(glBlendFuncSeparate_impl,
             thread,
             GLBLENDFUNCSEPARATE_ID,
             RPC_ENUM(srcRGB),
             RPC_ENUM(dstRGB),
             RPC_ENUM(srcAlpha),
             RPC_ENUM(dstAlpha));
}