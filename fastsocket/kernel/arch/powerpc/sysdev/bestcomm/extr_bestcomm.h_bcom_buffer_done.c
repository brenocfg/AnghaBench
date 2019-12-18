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
struct bcom_task {int /*<<< orphan*/  outdex; } ;
struct bcom_bd {int status; } ;

/* Variables and functions */
 int BCOM_BD_READY ; 
 struct bcom_bd* bcom_get_bd (struct bcom_task*,int /*<<< orphan*/ ) ; 
 scalar_t__ bcom_queue_empty (struct bcom_task*) ; 

__attribute__((used)) static inline int
bcom_buffer_done(struct bcom_task *tsk)
{
	struct bcom_bd *bd;
	if (bcom_queue_empty(tsk))
		return 0;

	bd = bcom_get_bd(tsk, tsk->outdex);
	return !(bd->status & BCOM_BD_READY);
}