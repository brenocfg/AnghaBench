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
typedef  TYPE_1__* thread_t ;
typedef  int ast_t ;
struct TYPE_3__ {int ast; } ;

/* Variables and functions */
 int AST_PER_THREAD ; 
 int* ast_pending () ; 

void
ast_context(thread_t thread)
{
	ast_t *pending_ast = ast_pending();

	*pending_ast = ((*pending_ast & ~AST_PER_THREAD) | thread->ast);
}