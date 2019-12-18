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
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int dummy; } ;
struct qla4_work_evt {int type; int /*<<< orphan*/  list; } ;
typedef  enum qla4_work_type { ____Placeholder_qla4_work_type } qla4_work_type ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct qla4_work_evt* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct qla4_work_evt *
qla4xxx_alloc_work(struct scsi_qla_host *ha, uint32_t data_size,
		   enum qla4_work_type type)
{
	struct qla4_work_evt *e;
	uint32_t size = sizeof(struct qla4_work_evt) + data_size;

	e = kzalloc(size, GFP_ATOMIC);
	if (!e)
		return NULL;

	INIT_LIST_HEAD(&e->list);
	e->type = type;
	return e;
}