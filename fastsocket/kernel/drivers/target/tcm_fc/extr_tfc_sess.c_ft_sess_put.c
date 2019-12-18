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
struct TYPE_2__ {int /*<<< orphan*/  refcount; } ;
struct ft_sess {TYPE_1__ kref; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ft_sess_free ; 
 int /*<<< orphan*/  kref_put (TYPE_1__*,int /*<<< orphan*/ ) ; 

void ft_sess_put(struct ft_sess *sess)
{
	int sess_held = atomic_read(&sess->kref.refcount);

	BUG_ON(!sess_held);
	kref_put(&sess->kref, ft_sess_free);
}